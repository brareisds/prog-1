CC = gcc
CFLAGS = -g  -Wall -Werror -Wextra -pedantic


main: libAgenda.o main.o
	$(CC) main.o libAgenda.o -o main                          
                                                                                
main.o : main.c
	$(CC) $(CFLAGS) -c main.c

libAgenda.o : libAgenda.c
	$(CC) $(CFLAGS) -c libAgenda.c

clean :
	rm *.o main
