all: ms_cli
clean:
	rm -rf ms_cli* ./bin

CF = -I include -c -fno-builtin -Werror -Wall -Wextra -Wshadow 

bin/mergesort.o: include/mergesort.h src/mergesort.c
	gcc $(CF)$ src/mergesort.c -o bin/mergesort.o
bin/ms_cli.o: src/ms_cli.c bin/mergesort.o include/mergesort.h
	gcc $(CF)$ src/ms_cli.c -o bin/ms_cli.o
bin: 
	mkdir bin
ms_cli: bin bin/ms_cli.o
	gcc -o ms_cli bin/*.o
.PHONY: all clean
