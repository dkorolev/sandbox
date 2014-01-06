namespace cpp dima

struct Entry {
  1: i64 ms,
  2: i64 value,
  3: string message
}

struct Stats {
  1: i32 count,
  2: i64 sum,
  3: list<Entry> last_three
}

service Dima {
   oneway void push(1:Entry e),
   Stats stats()
}
