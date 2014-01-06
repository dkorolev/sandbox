all: client server

client: CppClient.cpp gen-cpp/deps
	g++ -o $@ $< gen-cpp/*.o -static -lthrift

server: CppServer.cpp gen-cpp/deps
	g++ -o $@ $< gen-cpp/*.o -static -lthrift

gen-cpp/deps: tutorial.thrift shared.thrift
	thrift --gen cpp -r $<
	(cd gen-cpp; for i in `ls *.cpp | grep -v skeleton` ; do g++ -c $$i ; done)
	echo OK >$@

clean:
	rm -rf client server gen-cpp

