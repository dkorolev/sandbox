#include "gen-cpp/DimaService.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <chrono>
#include <deque>

uint64_t js_date_now() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace ::dima;

class DimaHandler : virtual public DimaServiceIf {
 public:
  void dima_push(const DimaEntry& e) {
    ++count;
    sum += e.value;
    entries.push_back(e);
    while (entries.size() > 3) {
      entries.pop_front();
    }
    std::cout << "Ping: " << (js_date_now() - e.ms) << "ms" << std::endl;
    std::cout << e.ms << ' ' << e.value << ' ' << e.message << ' ' << sizeof(e.ms) << std::endl;
  }
  void dima_stats(DimaStats& out_stats) {
    out_stats.count = count;
    out_stats.sum = sum;
    out_stats.last_three.clear();
    for (auto e : entries) {
      out_stats.last_three.push_back(e);
    }
  }

 private:
  uint32_t count = 0;
  uint64_t sum = 0;
  std::deque<DimaEntry> entries;
};

int main() {
  const int port = 9090;
  boost::shared_ptr<DimaHandler> handler(new DimaHandler());
  boost::shared_ptr<TProcessor> processor(new DimaServiceProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  TSimpleServer(processor, serverTransport, transportFactory, protocolFactory).serve();
}
