CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wvla -fsanitize=address
all: tinyprintf.o

tinyprintf.o:
	$(CC) $(CFLAGS) -c -o src/tinyprintf.o src/tinyprintf.c
check: tinyprintf.o
	$(CC) $(CFLAGS) src/tinyprintf.o -o tests/test tests/test.c -lcriterion
	./tests/test

clean:
	rm -f tests/test src/tinyprintf.o
