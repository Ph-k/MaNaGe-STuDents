# Code from https://github.com/Ph-k/Manage-STuDents. Philippos Koumparos (github.com/Ph-k)

CC = gcc
objects = main.o Controller.o fileReader.o HashTable.o LinkedList.o Student.o
cflags = -Wall
program = mngstd

$(program): $(objects)
	gcc $(objects) -o $(program)
	
main.o: main.c
	$(CC) $(cflags) -c main.c

Controller.o: Controller.c Controller.h
	$(CC) $(cflags) -c Controller.c

fileReader.o: fileReader.c fileReader.h
	$(CC) $(cflags) -c fileReader.c

HashTable.o: HashTable.c HashTable.h
	$(CC) $(cflags) -c HashTable.c

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) $(cflags) -c LinkedList.c

Student.o: Student.c Student.h
	$(CC) $(cflags) -c Student.c

run: $(program)
	./$(program)

clean:
	rm -f $(program)
	rm -f $(objects)
