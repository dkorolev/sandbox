#include <cstdio>
#include <cstring>

int main() {
  FILE* f;
  f = fopen("dima_test.txt", "w");
  fprintf(f, "foo\nbar");
  fclose(f);
  f = fopen("dima_test.txt", "r");
  char s[1024];
  while (fgets(s, sizeof(s), f)) {
    printf("%d\n", strlen(s));
  }
  fclose(f);
}
