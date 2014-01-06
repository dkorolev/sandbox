namespace cpp dima

struct DimaEntry {
  1: i64 ms,
  2: i64 value,
  3: string message
}

struct DimaStats {
  1: i32 count,
  2: i64 sum,
  3: list<DimaEntry> last_three
}

service DimaService {
   void dima_push(1:DimaEntry e),
   DimaStats dima_stats()
}
