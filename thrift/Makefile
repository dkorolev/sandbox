CC=g++ --std=c++11

all: client server gen-nodejs/OK node_modules/OK

client: client.cc gen-cpp/OK
	${CC} -o $@ $< gen-cpp/*.o -static -lthrift

server: server.cc gen-cpp/OK
	${CC} -o $@ $< gen-cpp/*.o -static -lthrift

gen-cpp/OK: dima.thrift
	thrift --gen cpp -r $<
	(cd gen-cpp; for i in `ls *.cpp | grep -v skeleton` ; do g++ -c $$i ; done)
	echo OK >$@

gen-nodejs/OK: dima.thrift
	thrift --gen js:node dima.thrift
	echo OK >$@

node_modules/OK: package.json
	npm install
	echo OK >$@

clean:
	rm -rf client server gen-cpp

