# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = parenteses.o libpilha.o 
     
all: parenteses.o libpilha.o
	$(CC) -o parenteses parenteses.o libpilha.o $(LDFLAGS)

libpilha.o: libpilha.c
	$(CC) -c $(CFLAGS) libpilha.c

parenteses.o: parenteses.c
	$(CC) -c $(CFLAGS) parenteses.c

clean:
	rm -f $(objects) parenteses


