CFLAGS = -g -O0 
object = odb.o hash.o
CC = gcc 

all:$(object)


odb.o: odb.c odb.h
	$(CC) -c odb.c
hash.o: hash.c hash.h
	$(CC) -c hash.c
test_odb: test_odb.c test_odb.h odb.c odb.h initdir.c initdir.h hash.c hash.h
	$(CC) -o test_odb $(CFLAGS) test_odb.c odb.c initdir.c hash.c
test_hash: test_hash.c hash.c hash.h
	$(CC) -o test_hash $(CFLAGS) test_hash.c hash.c
clean:
	rm $(object) test_odb 
