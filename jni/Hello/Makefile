JDK_PATH=/usr/lib/jvm/default-java/include

.PHONY: all clean run

all: Hello.class HelloWorld.class libHello.so

libHello.so: libHello.o
	$(CC) -o $@ -shared $^

libHello.o: Hello.c HelloWorld.h
	$(CC) -I $(JDK_PATH) -c -fPIC -O3 -mtune=native -o $@ $<

HelloWorld.h: HelloWorld.class
	classfile="$<"; \
	javah -o $@ $${classfile%.class}

%.class: %.java
	javac -classpath . $<

clean:
	rm *.class *.o *.so *.h

run:
	LD_LIBRARY_PATH=. java Hello
