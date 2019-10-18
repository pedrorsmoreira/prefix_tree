CFLAGS= -lm -O2 -Ofast -std=gnu11

default: program

program: main.c api.c fifo.c list.c node.c utils.c
	gcc main.c api.c fifo.c list.c node.c utils.c -o PrefixTree $(CFLAGS)

clean:
	rm -f *.o PrefixTree