CFLAGS=-O3 -mtune=native

.PHONY: clean

test: test.o cksum1.o cksum2.o cksum3.o tsc.o 
	gcc -o $@ $^

test.o: test.c
	gcc -O0 -mtune=native -c -o $@ $<

cksum1.o: cksum1.c
cksum2.o: cksum2.c

%.o: %.asm
	nasm -f elf64 -o $@ $<

clean:
	rm *.o test
