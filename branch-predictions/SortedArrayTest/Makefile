CFLAGS=-O3 -mtune=native -DSORTED_ARRAY

SortedArrayTest: SortedArrayTest.o
	$(CC) -o $@ $^

SortedArrayTest.o: SortedArrayTest.c

clean:
	rm SortedArrayTest.o SortedArrayTest
