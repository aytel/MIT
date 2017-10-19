all: main
clean:
	rm -rf main.* ./bin

CF = -I include -c -fno-builtin -lexpat 

bin/phonebook.o: src/phonebook.c include/phonebook.h
	gcc $(CF)$ src/phonebook.c -o bin/phonebook.o
bin/main.o: src/main.c bin/phonebook.o include/phonebook.h
	gcc $(CF)$ src/main.c -o bin/main.o
bin: 
	mkdir bin
main: bin bin/main.o
	gcc bin/*.o -lexpat -o main
.PHONY: all clean
