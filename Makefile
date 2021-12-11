CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror
LIBS=-lm

formatter: main.o
	$(CC) $(CFLAGS) $(LIBS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	rm *.o
	rm formatter

