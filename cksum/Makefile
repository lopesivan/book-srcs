.PHONY: clean

test: test.o cksum_rfc.o cksum2.o cksum3.o tsc.o 
	gcc -o $@ $^

test.o: test.c
	gcc -O0 -c -o $@ $<

%.o: %.c
	gcc -O3 -mtune=native -c -o $@ $<

%.o: %.asm
	nasm -f elf64 -o $@ $<

clean:
	rm *.o test
