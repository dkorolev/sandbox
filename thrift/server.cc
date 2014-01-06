#include "gen-cpp/Dima.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <deque>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace ::dima;

class DimaHandler : virtual public DimaIf {
 public:
  void push(const Entry& e) {
    ++count;
    sum += e.value;
    entries.push_back(e);
    while (entries.size() > 3) {
      entries.pop_front();
    }
    std::cout << e.ms << ' ' << e.value << ' ' << e.message << ' ' << sizeof(e.ms) << std::endl;
  }
  void stats(Stats& out_stats) {
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
  std::deque<Entry> entries;
};

int main() {
  const int port = 9090;
  boost::shared_ptr<DimaHandler> handler(new DimaHandler());
  boost::shared_ptr<TProcessor> processor(new DimaProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  TSimpleServer(processor, serverTransport, transportFactory, protocolFactory).serve();
}
