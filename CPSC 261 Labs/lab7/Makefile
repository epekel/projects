CC = gcc
CFLAGS = -Wall -g -O3

all:	phil-rightfork phil-ordered phil-random tictactoe tictacmany

tictactoe: tictactoe.c
	$(CC) $(CFLAGS) -o tictactoe tictactoe.c -lpthread

tictacmany: tictacmany.c
	$(CC) $(CFLAGS) -o tictacmany tictacmany.c -lpthread

phil-rightfork:	phil-rightfork.c
	$(CC) $(CFLAGS) -o phil-rightfork phil-rightfork.c -lpthread

phil-ordered:	phil-ordered.c
	$(CC) $(CFLAGS) -o phil-ordered phil-ordered.c -lpthread

phil-random:	phil-random.c
	$(CC) $(CFLAGS) -o phil-random phil-random.c -lpthread

clean:
	rm -f phil-rightfork phil-ordered phil-random tictactoe tictacmany *.o *~
