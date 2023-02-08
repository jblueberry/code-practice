# compile main.cc

all: test

test: test.cc task.h thread_pool.h safe_queue.h
	g++ -o bin/test test.cc

clean:
	rm -f test