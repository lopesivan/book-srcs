PYTHON=python2.7
PYTHON_LIB=$(PYTHON)
PYTHON_INCLUDE=/usr/include/$(PYTHON)

.PHONY: clean

call: call.o
	$(CC) -o $@ $^ -l$(PYTHON_LIB)

call.o: call.c
	$(CC) -I $(PYTHON_INCLUDE) -O3 -mtune=native -c -o $@ $<

clean:
	rm *.o call
