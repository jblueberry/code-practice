# compile main.cc

all: test

test: test.cc task.h thread_pool.h safe_queue.h
	mkdir -p bin
	g++ -o bin/test test.cc -pthread

clean:
	rm -f -r bin