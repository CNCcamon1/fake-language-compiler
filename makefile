CC=gcc -g
CFLAGS=-I.

fake-language-compiler: init.cpp
	$(CC) $(LDFLAGS) init.cpp scanner.cpp -lstdc++ -o fake-language-compiler.o $(LDLIBS)