all: a.out
CC=g++
CPPFLAGS=-O3

a.out: simple.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f a.out
