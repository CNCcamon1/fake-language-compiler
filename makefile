CC=gcc -g
CFLAGS=-I.

fake-language-compiler: init.cpp
	$(CC) $(LDFLAGS) init.cpp parser.cpp scanner.cpp -lstdc++ -o fake-language-compiler.o $(LDLIBS)