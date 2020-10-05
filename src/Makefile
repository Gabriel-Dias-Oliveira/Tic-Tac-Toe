CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: tic-tac-toe

tic-tac-toe: tic-tac-toe-main.c
	gcc $(CFLAGS) -c tic-tac-toe-functions.c $(LDFLAGS)
	gcc $(CFLAGS) -c tic-tac-toe-main.c $(LDFLAGS)
	gcc $(CFLAGS) -o tic-tac-toe tic-tac-toe-main.o tic-tac-toe-functions.o $(LDFLAGS)

clean:
	rm -f tic-tac-toe
	rm -f *.o
