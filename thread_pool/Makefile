# compile main.cc

all: test test2

test: test.cc task.h thread_pool.h safe_queue.h
	mkdir -p bin
	g++ -o bin/test test.cc -pthread

test2: test2.cc
	mkdir -p bin
	g++ -o bin/test2 test2.cc -pthread -O0

clean:
	rm -f -r bin