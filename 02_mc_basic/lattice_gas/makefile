all: a.out
CC=g++
CPPFLAGS=-O3

a.out: lattice_gas.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f a.out
