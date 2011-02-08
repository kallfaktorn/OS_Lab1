IDIR= ./libsh
LDIR= ./libsh
VPATH= ./libsh
CC=gcc
CFLAGS= -g -I$(IDIR) -Wall
DEPS= parse.h libsh.h 

OBJ_MAIN= main.o libsh.o 
OBJ_LSH= parse.o lsh.o libsh.o

LIBS= -lreadline -lncurses
BIN= lsh

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ_MAIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

lsh: $(OBJ_LSH)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -f *.o; rm main; rm lsh

all:
	make clean; make; make lsh
