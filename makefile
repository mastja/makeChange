# macro tells which compiler to use
CC = g++

# macro says using c++11 standard
CFLAGS = -std=c++11 -c

# run "make all" to run makeChange
all: makeChange

# make the makeChange sort program
change: makeChange.o
	$(CC) makeChange.o -o bad

makeChange.o:
	$(CC) $(CFLAGS) makeChange.cpp


clean:
	rm *.o
	rm -f change.txt
	rm makeChange