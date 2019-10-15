FLAGS=-Wall -Werror -g -fsanitize=address
CC=gcc

memgrind: memgrind.o mymalloc.o
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c mymalloc.h
	$(CC) $(FLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o *.i *.bc *.s memgrind
