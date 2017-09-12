all: lab1
clean:
	rm -rf lab1 *.o
algorithm.o: algorithm.c util.o
	gcc -c algorithm.c
io.o: io.c
	gcc -c io.c
util.o: util.c io.o
	gcc -c util.c
main.o: main.c algorithm.o
	gcc -c main.c
lab1: main.o
	gcc -o lab1 main.o io.o util.o algorithm.o
.PHONY: all clean
