all: main
clean:
	rm -rf main.* ./bin

CF = -I include -c -fno-builtin 

bin/clist.o: src/clist.c include/clist.h
	gcc $(CF)$ src/clist.c -o bin/clist.o
bin/position.o: src/position.c bin/clist.o include/clist.h
	gcc $(CF)$ src/position.c -o bin/position.o
bin/main.o: src/main.c bin/clist.o include/clist.h bin/position.o include/position.h
	gcc $(CF)$ src/main.c -o bin/main.o
bin: 
	mkdir bin
main: bin bin/main.o
	gcc -o main bin/*.o
.PHONY: all clean
