// Requires --std=c++0x.
//
// Defines the allocator for the memory the code from which can be directly executed.
//
// const unsigned char machine_code[] = { .. };
// std::vector<unsigned char, exec_friendly_allocator<unsigned char>>
//   static_buf(machine_code, machine_code + sizeof(machine_code));
// typedef double (*FUNCTION)(double);
// FUNCTION eval_static = reinterpret_cast<FUNCTION>(&static_buf[0]);
// double r = eval_static(42.0);

#ifndef EXEC_FRIENDLY_ALLOCATOR_H
#define EXEC_FRIENDLY_ALLOCATOR_H

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include <limits>
#include <vector>

template<typename T> struct exec_friendly_allocator {
  static_assert(sizeof(T) == 1, "exec_friendly_allocator operates on unit size types only.");

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
    void* tmp;
    if (!posix_memalign(&tmp, getpagesize(), size * sizeof(T))) {
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

#endif
