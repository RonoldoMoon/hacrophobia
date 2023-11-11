CC=gcc
CFLAGS=-Wall
LIBS=

hacrophobia: hacrophobia.c server.c handler.c
	$(CC) $(CFLAGS) -c hacrophobia.c server.c handler.c
	$(CC) *.o -o hacrophobia

clean:
	rm *.o
	rm hacrophobia
