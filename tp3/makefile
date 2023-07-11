# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_pilha.o libpilha.o 
     
all: testa_pilha.o libpilha.o
	$(CC) -o testa_pilha testa_pilha.o libpilha.o $(LDFLAGS)

libpilha.o: libpilha.c
	$(CC) -c $(CFLAGS) libpilha.c

testa_pilha.o: testa_pilha.c
	$(CC) -c $(CFLAGS) testa_pilha.c

clean:
	rm -f $(objects) testa_pilha


