IDIR= ./libsh
LDIR= ./libsh
VPATH= ./libsh
CC=gcc
CFLAGS= -I$(IDIR)
DEPS= libsh.h
OBJ= main.o libsh.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

