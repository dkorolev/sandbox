#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

#include <vector>
#include <cassert>
#include <cstring>

#include "exec_friendly_allocator.h"

typedef int (*DIM)();
typedef double (*EVAL)(const double*, double*);

int main() {
  // 0. Run function from static machine code.
  {
    // Machine code is copied from the output of step 3 below.
    const unsigned char code[] = { 0x48,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x40,0x48,0x89,0x06,0xf3,0x0f,0x7e,0x06,0xc3, };
    std::vector<unsigned char, exec_friendly_allocator<unsigned char> > static_buf(code, code + sizeof(code)/sizeof(code[0]));
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
