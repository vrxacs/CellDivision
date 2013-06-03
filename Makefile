CC = g++
CFLAGS = -Wall -pedantic -O3

all: CellDivision.out

CellDivision.out: main.cpp cells.cpp
	$(CC) $(CFLAGS) cells.cpp main.cpp