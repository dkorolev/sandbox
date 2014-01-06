CC=g++ --std=c++11

all: client server

client: client.cc gen-cpp/deps
	${CC} -o $@ $< gen-cpp/*.o -static -lthrift

server: server.cc gen-cpp/deps
	${CC} -o $@ $< gen-cpp/*.o -static -lthrift

gen-cpp/deps: dima.thrift
	thrift --gen cpp -r $<
	(cd gen-cpp; for i in `ls *.cpp | grep -v skeleton` ; do g++ -c $$i ; done)
	echo OK >$@

clean:
	rm -rf client server gen-cpp

