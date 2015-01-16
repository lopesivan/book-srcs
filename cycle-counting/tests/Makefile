CFLAGS=-O3 -mtune=native

test: test.o test2.o
	gcc -o $@ $^

test.o: test.c
	gcc $(CFLAGS) -g -c -o $@ $<

test2.o: test2.asm
	nasm -g -f elf64 -o $@ $<
