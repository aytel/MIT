all: pqsort

clean:
	rm -rf pqsort ./bin

CF = -I include -c -Wall -Wextra -Werror -std=c++11 -pthread 

./bin/thread_pool.o: ./include/thread_pool.h ./src/thread_pool.cpp 
	g++ $(CF)$ ./src/thread_pool.cpp -o ./bin/thread_pool.o
./bin/pqsort.o: ./src/pqsort.cpp ./bin/thread_pool.o
	g++ $(CF)$ ./src/pqsort.cpp -o ./bin/pqsort.o
bin: 
	mkdir bin
pqsort: bin ./bin/pqsort.o
	g++ -pthread -o pqsort ./bin/*.o

.PHONY: all clean
