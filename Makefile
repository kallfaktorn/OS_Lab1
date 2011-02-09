IDIR= ./libsh
LDIR= ./libsh
VPATH= ./libsh
CC=gcc
CFLAGS= -g -I$(IDIR) -Wall
DEPS= parse.h libsh.h cd.h

OBJ_LSH= parse.o lsh.o libsh.o cd.o

LIBS= -lreadline -lncurses
BIN= lsh

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lsh: $(OBJ_LSH)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -f *.o; rm lsh

all:
	make clean; make
