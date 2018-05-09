CC=gcc
CFLAGS=-Wall -ansi -pedantic
DEPS=$(wildcard libs/*.c)
OBJ=$(wildcard obj/*.o)
LINKS=-lpthread -lrt

all: tdm1 tdm2 tdm3 tdm4 tdm5

tdm1: tdm1_test1c tdm1_test2a

tdm1_test1c: build_deps
	$(CC) $(OBJ) tests/tdm1/test1c.c $(CFLAGS) -o $@.o

tdm1_test2a: build_deps
	$(CC) $(OBJ) tests/tdm1/test2a.c $(CFLAGS) -o $@.o

tdm2: tdm2_testIB1 tdm2_testIB2 tdm2_testIB3 tdm2_testII1 tdm2_testIII1 tdm2_testIII2 tdm2_testIII3

tdm2_testIB1: build_deps
	$(CC) $(OBJ) tests/tdm2/testIB1.c $(CFLAGS) -o $@.o

tdm2_testIB2: build_deps
	$(CC) $(OBJ) tests/tdm2/testIB2.c $(CFLAGS) -o $@.o

tdm2_testIB3: build_deps
	$(CC) $(OBJ) tests/tdm2/testIB3.c $(CFLAGS) -o $@.o

tdm2_testII1: build_deps tdm2_testIB1
	$(CC) $(OBJ) tests/tdm2/testII1.c $(CFLAGS) -o $@.o

tdm2_testIII1: build_deps
	$(CC) $(OBJ) tests/tdm2/testIII1.c $(CFLAGS) -o $@.o

tdm2_testIII2: build_deps
	$(CC) $(OBJ) tests/tdm2/testIII2.c $(CFLAGS) -o $@.o

tdm2_testIII3: build_deps
	$(CC) $(OBJ) tests/tdm2/testIII3.c $(CFLAGS) -o $@.o

tdm3: tdm3_testIB2 tdm3_testIII

tdm3_testIB2: build_deps
	$(CC) $(OBJ) tests/tdm3/testIB2.c $(CFLAGS) -o $@.o

tdm3_testIII: build_deps
	$(CC) $(OBJ) tests/tdm3/testIII.c $(CFLAGS) -o $@.o

tdm4: tdm4_testIB tdm4_testIIB

tdm4_testIB: build_deps
	$(CC) $(OBJ) tests/tdm4/testIB.c $(CFLAGS) $(LINKS) -o $@.o

tdm4_testIIB: build_deps
	$(CC) $(OBJ) tests/tdm4/testIIB.c $(CFLAGS) $(LINKS) -o $@.o

tdm5: tdm5_test

tdm5_test: build_deps
	$(CC) $(OBJ) tests/tdm5/test.c $(CFLAGS) $(LINKS) -o $@.o

build_deps:
	$(CC) $(CFLAGS) -c $(DEPS) && mv *.o obj

clean:
	rm -vf *.o obj/*.o
