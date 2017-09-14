all: lab1
clean:
	rm -rf lab1 ./bin

CF = -I include -c 

./bin/algorithm.o: ./src/algorithm.c ./bin/util.o
	gcc $(CF)$ ./src/algorithm.c -o ./bin/algorithm.o
./bin/io.o: ./src/io.c
	gcc $(CF)$ ./src/io.c -o ./bin/io.o
./bin/util.o: ./src/util.c ./bin/io.o
	gcc $(CF)$ ./src/util.c -o ./bin/util.o
./bin/main.o: ./src/main.c ./bin/algorithm.o
	gcc $(CF)$ ./src/main.c -o ./bin/main.o
bin: 
	mkdir bin
lab1: bin ./bin/main.o
	gcc -o lab1 ./bin/*.o
.PHONY: all clean
