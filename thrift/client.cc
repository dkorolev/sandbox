#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "./gen-cpp/DimaService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace dima;

int main(int argc, char** argv) {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  DimaServiceClient client(protocol);

  try {
    transport->open();

    DimaEntry e;
    e.ms = 42;
    e.value = 123;
    e.message = "Hello, World!";
    client.dima_push(e);
    
    DimaStats s;
    client.dima_stats(s);
    std::cout << s.count << ' ' << s.sum << ' ' << s.last_three.size() << std::endl;

    transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }
}
