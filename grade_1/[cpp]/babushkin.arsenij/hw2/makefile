all: lab2
clean:
	rm -rf lab2* ./bin

CF = -I include -c -fno-builtin 

bin/str.o: src/str.c include/str.h
	gcc $(CF)$ src/str.c -o bin/str.o
bin/test_str.o: src/test_str.c bin/str.o include/str.h
	gcc $(CF)$ src/test_str.c -o bin/test_str.o
bin/test.o: src/test.c bin/test_str.o include/test_str.h
	gcc $(CF)$ src/test.c -o bin/test.o
bin: 
	mkdir bin
lab2: bin bin/test.o
	gcc -o lab2 bin/*.o
.PHONY: all clean
