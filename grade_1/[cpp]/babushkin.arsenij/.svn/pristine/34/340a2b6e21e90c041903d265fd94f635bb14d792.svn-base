all: pose_db
clean:
	rm -rf pose_db* ./bin

CF = -I include -c -fno-builtin 

bin/clist.o: src/clist.c include/clist.h
	gcc $(CF)$ src/clist.c -o bin/clist.o
bin/main.o: src/main.c bin/clist.o include/clist.h
	gcc $(CF)$ src/main.c -o bin/main.o
bin: 
	mkdir bin
pose_db: bin bin/main.o
	gcc -o pose_db bin/*.o
.PHONY: all clean
