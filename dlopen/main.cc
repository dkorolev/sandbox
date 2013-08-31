#include <stdio.h>
#include <dlfcn.h>

typedef double (*SUM)(const double*);

int main() {
  void *lib = dlopen("./lib.so", RTLD_LAZY);
  if (lib) {
    SUM sum = reinterpret_cast<SUM>(dlsym(lib, "sum"));
    double x[2] = { 1, 2 }, y[2] = { 99, 1 };
    printf("OK: %.0lf, %.0lf\n", sum(x), sum(y));
    dlclose(lib);
  } else {
    printf("Error loading library.\n");
  }
}
