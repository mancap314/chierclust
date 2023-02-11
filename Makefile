CC=gcc
CFLAGS=-Wall -Werror -I.
DEPS = hierclust.h hierclust_utils.h

test: hierclust.c hierclust_utils.c test.c $(DEPS)
	$(CC) -o $@.o $^ $(CFLAGS)
	./$@.o


debug: hierclust.c hierclust_utils.c test.c $(DEPS)
	$(CC) -o $@.o $^ $(CFLAGS) -g
	gdb $@.o


.PHONY: clean

clean:
	rm -f *.o
