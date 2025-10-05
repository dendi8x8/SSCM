CC=gcc
CFLAGS=-c -Wall

all: sscm

run: sscm
	./build/sscm

sscm: main.o file_utils.o base_skinpack.o 
	$(CC) main.o file_utils.o base_skinpack.o -o sscm
	mv sscm build

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c

file_utils.o: src/file_utils.c
	$(CC) $(CFLAGS) src/file_utils.c

base_skinpack.o: src/base_skinpack.c
	$(CC) $(CFLAGS) src/base_skinpack.c

clean:
	rm -rf *.o sscm


