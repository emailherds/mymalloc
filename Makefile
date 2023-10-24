OBJS	= mymalloc.o memgrind.o
SOURCE	= mymalloc.c memgrind.c
HEADER	= mymalloc.h
OUT	= memgrind
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

mymalloc.o: mymalloc.c
	$(CC) $(FLAGS) mymalloc.c -std=c99

memgrind.o: memgrind.c
	$(CC) $(FLAGS) memgrind.c -std=c99
