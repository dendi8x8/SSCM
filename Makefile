CC=gcc
CFLAGS=-c -Wall --std=c99 -g -D_XOPEN_SOURCE=700 

all: sscm

run: sscm
	./build/sscm

sscm: main.o file_utils.o base_skinpack.o 
	$(CC) main.o file_utils.o base_skinpack.o -o sscm
	rm -rf *.o
	mv sscm build

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

file_utils.o: src/file_utils.c
	$(CC) $(CFLAGS) src/file_utils.c

base_skinpack.o: src/base_skinpack.c
	$(CC) $(CFLAGS) src/base_skinpack.c

clean:
	rm -rf *.o build/sscm


