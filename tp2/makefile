#
# A simple makefile for managing build of project composed of C source files.
#


# It is likely that default C compiler is already gcc, but explicitly
# set, just to be sure
CC = gcc

# The CFLAGS variable sets compile flags for gcc:
#  -g        compile with debug information
#  -Wall     give verbose compiler warnings

CFLAGS = -g  -Wall -Werror -Wextra -pedantic
LDFLAGS = -lm

main: libAgenda.o main.o
	$(CC) main.o libAgenda.o -o tp2  $(LDFLAGS)

main.o : main.c	
	$(CC) $(CFLAGS) -c main.c

cartesiano.o : libAgenda.c
	$(CC) $(CFLAGS) -c libAgenda.c

clean :
	rm *.o tp2

