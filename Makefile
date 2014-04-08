CFLAGS = -g -O0 -Wall
object = odb.o hash.o initdir.o test_odb.o test_hash.o
target = test_odb test_hash
CC = gcc


odb.o: odb.c odb.h common.h
	$(CC) -c odb.c
hash.o: hash.c hash.h common.h
	$(CC) -c hash.c
initdir.o: initdir.c initdir.h common.h
	$(CC) -c initdir.c
test_odb.o: test_odb.c
	$(CC) -c test_odb.c
test_hash.o: test_hash.c
	$(CC) -c test_hash.c
test_odb: test_odb.o initdir.o hash.o odb.o
	$(CC) -o $@ $(CFLAGS) test_odb.o initdir.o hash.o odb.o
test_hash: test_hash.o hash.o
	$(CC) -o $@ $(CFLAGS) test_hash.o hash.o
clean:
	-rm -rf $(object) $(target) nginx*/objects etc/objects frist/objects 
clear:
	-rm -rf nginx*/objects etc/objects frist/objects
