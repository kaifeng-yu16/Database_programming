CC=g++
CFLAGS=-O3
EXTRAFLAGS=-lpqxx -lpq

all: test

test: main.cpp exerciser.h exerciser.cpp query_funcs.h query_funcs.cpp table_funcs.h table_funcs.cpp table_cmd.h
	$(CC) $(CFLAGS) -o test main.cpp exerciser.cpp query_funcs.cpp table_funcs.cpp $(EXTRAFLAGS)

clean:
	rm -f *~ *.o test

clobber:
	rm -f *~ *.o
