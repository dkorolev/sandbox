#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <vector>
#include <cassert>
#include <cstring>

// struct exec_friendly_allocator requires --std=c++0x.
#include <limits>
template<typename T> struct exec_friendly_allocator {
  static_assert(sizeof(T) == 1, "exec_friendly_allocator operates on unit sized types only.");

  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  template<typename U> struct rebind {
    typedef exec_friendly_allocator<U> other;
  };

  inline explicit exec_friendly_allocator() {}
  inline ~exec_friendly_allocator() {}
  inline explicit exec_friendly_allocator(exec_friendly_allocator const&) {}
  template<typename U> inline explicit exec_friendly_allocator(exec_friendly_allocator<U> const&) {}

  inline pointer address(reference r) { return &r; }
  inline const_pointer address(const_reference r) { return &r; }

  inline pointer allocate(size_type size, typename std::allocator<void>::const_pointer = nullptr) {
    const int pagesize = getpagesize();
    void* tmp;
    if (!posix_memalign(&tmp, pagesize, size * sizeof(T))) {
      mprotect(tmp, size, PROT_READ | PROT_WRITE | PROT_EXEC);
      return reinterpret_cast<pointer>(tmp);
    } else {
      throw std::bad_alloc();
    }
  }

  inline void deallocate(pointer p, size_type) { 
    free(p);
  }

  inline size_type max_size() const { 
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  inline void construct(pointer p, const T& t) { new(p) T(t); }
  inline void destroy(pointer p) { p->~T(); }

  inline bool operator==(exec_friendly_allocator const&) { return true; }
  inline bool operator!=(exec_friendly_allocator const& a) { return !operator==(a); }
};

typedef int (*DIM)();
typedef double (*EVAL)(const double*, double*);

int main() {
  // 0. Run the function from static data.
  {
    // Machine code is copied from the output of step 3 below.
    const unsigned char binary[] = { 0x48,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x40,0x48,0x89,0x06,0xf3,0x0f,0x7e,0x06,0xc3, };
    std::vector<unsigned char, exec_friendly_allocator<unsigned char> > static_buf(binary, binary + sizeof(binary)/sizeof(binary[0]));
    EVAL eval_static = reinterpret_cast<EVAL>(&static_buf[0]);
    std::vector<double> x(1, 1.0);
    std::vector<double> a(1);
    printf("eval_static({1}) == %.3lf\n", eval_static(&x[0], &a[0]));
  }

  void *lib = dlopen("./lib.so", RTLD_LAZY);
  if (lib) {
    void* ptr_dim = dlsym(lib, "dim");
    void* ptr_eval = dlsym(lib, "eval");
    if (ptr_dim && ptr_eval) {
      // 1. Run the function from the library.
      DIM dim = reinterpret_cast<DIM>(ptr_dim);
      EVAL eval = reinterpret_cast<EVAL>(ptr_eval);
      printf("dim() == %d\n", dim());
      std::vector<double> x(dim(), 1.0);
      std::vector<double> a(dim());
      printf("eval({1}) == %.3lf\n", eval(&x[0], &a[0]));

      // 2. Create a copy of the function and run it.
      printf("ptr_dim=0x%08lx, ptr_eval=0x%08lx, 'sizeof'(eval)=%ld.\n",
             reinterpret_cast<size_t>(ptr_dim),
             reinterpret_cast<size_t>(ptr_eval),
             reinterpret_cast<size_t>(ptr_dim) - reinterpret_cast<size_t>(ptr_eval));
      const size_t size = reinterpret_cast<size_t>(ptr_dim) - reinterpret_cast<size_t>(ptr_eval);
      const unsigned char* begin = reinterpret_cast<const unsigned char*>(ptr_eval);
      const unsigned char* end = reinterpret_cast<const unsigned char*>(ptr_dim);
      printf("S=%ld\n", end-begin);
      std::vector<unsigned char, exec_friendly_allocator<unsigned char> > buf(begin, end);
      EVAL eval2 = reinterpret_cast<EVAL>(&buf[0]);
      printf("eval2({1}) == %.3lf\n", eval2(&x[0], &a[0]));

      // 3. Optional: write the function as the buffer for step 0.
      printf("unsigned char binary[] = { ");
      for (size_t i = 0; i < buf.size(); ++i) {
        printf("0x%02x,", buf[i]);
      }
      printf(" };\n");
    } else {
      printf("Error getting dim() or eval().\n");
    }
    dlclose(lib);
  } else {
    printf("Error loading library.\n");
  }
}
