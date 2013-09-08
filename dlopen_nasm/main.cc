#include <stdio.h>
#include <dlfcn.h>
#include <vector>

typedef int (*DIM)();
typedef double (*EVAL)(const double*, double*);

int main() {
  void *lib = dlopen("./lib.so", RTLD_LAZY);
  if (lib) {
    DIM dim = reinterpret_cast<DIM>(dlsym(lib, "dim"));
    EVAL eval = reinterpret_cast<EVAL>(dlsym(lib, "eval"));
    if (dim && eval) {
      printf("dim() == %d\n", dim());
      std::vector<double> x(dim(), 1.0);
      std::vector<double> a(dim());
      printf("eval({1}) == %.3lf\n", eval(&x[0], &a[0]));
    } else {
      printf("Error getting dim() or eval().\n");
    }
    dlclose(lib);
  } else {
    printf("Error loading library.\n");
  }
}
