CC = gcc
CFLAGS = -Wall -fPIC
AR = ar rcs
LDLIBS = -lm

all: program

# Object files
fred.o: fred.c
	$(CC) -c $(CFLAGS) fred.c

john.o: john.c
	$(CC) -c $(CFLAGS) john.c

bill.o: bill.c
	$(CC) -c $(CFLAGS) bill.c

sam.o: sam.c
	$(CC) -c $(CFLAGS) sam.c

libstatic.a: fred.o john.o
	$(AR) libstatic.a fred.o john.o

libshared.so: bill.o sam.o
	$(CC) -shared -o libshared.so bill.o sam.o $(LDLIBS)

libinterpose.so: interpose.c
	$(CC) -shared -o libinterpose.so interpose.c

interpose.o: interpose.c
	$(CC) -c -o interpose.o interpose.c

# Final program
program: program.c libstatic.a libshared.so interpose.o
	$(CC) -o program program.c interpose.o -L. -lstatic -lshared $(LDLIBS)

run:
	LD_LIBRARY_PATH=. LD_PRELOAD=./libinterpose.so ./program

clean:
	rm -f *.o *.a *.so program
