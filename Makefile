CC = g++

all:
	$(CC) -o vm8008.out 8008/vm8008.cc

clean:
	rm *.out
