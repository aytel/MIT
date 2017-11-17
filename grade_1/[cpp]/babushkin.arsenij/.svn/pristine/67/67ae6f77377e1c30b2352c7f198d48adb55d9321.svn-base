all: main
clean:
	rm -rf main.* ./bin

CF = -I include -c -fno-builtin -std=c99 -Wall -Werror 

bin/bmp.o: src/bmp.c include/bmp.h
	gcc $(CF)$ src/bmp.c -o bin/bmp.o
bin/main.o: src/main.c bin/bmp.o include/bmp.h
	gcc $(CF)$ src/main.c -o bin/main.o
bin: 
	mkdir bin
main: bin bin/main.o
	gcc bin/*.o -o main
.PHONY: all clean
