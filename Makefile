CFLAGS = -g -O0 
object = odb.o hash.o
CC = gcc 

all:$(object)


odb.o: odb.c odb.h
	$(CC) -c odb.c
hash.o: hash.c hash.h
	$(CC) -c hash.c
test_odb: test_odb.c test_odb.h odb.c odb.h
	$(CC) -o test_odb $(CFLAGS) test_odb.c odb.c
clean:
	rm $(object) test_odb 
