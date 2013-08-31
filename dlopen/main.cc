#include <stdio.h>
#include <dlfcn.h>

int main() {
  void *lib;
  double (*sum)(const double*);

  lib = dlopen("./lib.so", RTLD_LAZY);
  if (lib) {
    *(void **)(&sum) = dlsym(lib, "sum");
    double x[2] = { 1, 2 }, y[2] = { 99, 1 };
    printf("OK: %.0lf, %.0lf\n", sum(x), sum(y));
    dlclose(lib);
  } else {
    printf("Error loading library.\n");
  }
}
