all: main
clean:
	rm -rf main.* ./bin

CF = -I include -c -fno-builtin -std=c++11 -Wall -Werror -pedantic -Wextra 

bin/dsu.o: src/dsu.cpp include/dsu.h
	g++-4.9 $(CF)$ src/dsu.cpp -o bin/dsu.o

bin/board.o: src/board.cpp include/board.h bin/dsu.o
	g++-4.9 $(CF)$ src/board.cpp -o bin/board.o

bin/view.o: src/view.cpp include/view.h bin/board.o
	g++-4.9 $(CF)$ src/view.cpp -o bin/view.o

bin/main.o: src/main.cpp bin/view.o
	g++-4.9 $(CF)$ src/main.cpp -o bin/main.o

bin: 
	mkdir bin

main: bin bin/main.o
	g++-4.9 bin/*.o -o main

.PHONY: all clean
