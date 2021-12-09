CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror

formatter: main.o
	$(CC) $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
	rm formatter

