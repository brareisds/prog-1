# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_fila.o libfila.o 
     
all: testa_fila.o libfila.o
	$(CC) -o tp4 testa_fila.o libfila.o $(LDFLAGS)

libfila.o: libfila.c
	$(CC) -c $(CFLAGS) libfila.c

testa_fila.o: testa_fila.c
	$(CC) -c $(CFLAGS) testa_fila.c

clean:
	rm -f $(objects) tp4


