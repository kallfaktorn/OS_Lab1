IDIR= ./libsh
LDIR= ./libsh
VPATH= ./libsh
CC=cc
CFLAGS= -g -I$(IDIR)
DEPS= libsh.h
OBJ= main.o libsh.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	cc -o $@ $^ $(CFLAGS) $(LIBS)

clean: 
	rm -f *.o; rm main

all:
	make clean; make
