CC=gcc
CFLAGS=-c -g -Wall -Wdiscarded-qualifiers --std=c99 -D_XOPEN_SOURCE=700
LIBS=libs/libraylib

all: sscm

build: sscm

run: build
	./build/sscm

sscm: main.o file_utils.o skinpack.o alloc.o menu.o
	$(CC) main.o skinpack.o file_utils.o alloc.o menu.o $(LIBS) -o sscm
	mv sscm build

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

file_utils.o: src/file_utils.c src/include/file_utils.h
	$(CC) $(CFLAGS) src/file_utils.c

skinpack.o: src/skinpack.c src/include/skinpack.h
	$(CC) $(CFLAGS) src/skinpack.c

alloc.o: src/alloc.c src/include/alloc.h
	$(CC) $(CFLAGS) src/alloc.c

menu.o: src/menu.c src/include/menu.h
	$(CC) $(CFLAGS) src/menu.c libs/libraylib

clean:
	rm -rf *.o build/sscm


