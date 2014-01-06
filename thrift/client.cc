#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "./gen-cpp/Dima.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace dima;

int main(int argc, char** argv) {
  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  DimaClient client(protocol);

  try {
    transport->open();

    Entry e;
    e.ms = 42;
    e.value = 123;
    e.message = "Hello, World!";
    client.push(e);
    
    Stats s;
    client.stats(s);
    std::cout << s.count << ' ' << s.sum << ' ' << s.last_three.size() << std::endl;

    transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }
}
