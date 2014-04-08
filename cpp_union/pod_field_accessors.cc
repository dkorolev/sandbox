// The `Data` structure declares an array x[]
// of three elements: x[0], x[1], and x[2].
//
// `x[0]` is also accesible as `a`,
// `x[1]` as `b` and `x[2]` as `c`.

struct Data {
  union {
    struct {
      int a;
      int b;
      int c;
    };    
    int x[3];
  };
};

// Unit test that the accessors behave as expected.

struct DataTest {
  static Data data;
  static_assert(&data.a == &data.x[0], "&a != &x[0]");
  static_assert(&data.b == &data.x[1], "&b != &x[1]");
  static_assert(&data.c == &data.x[2], "&c != &x[2]");
};

int main() {}
