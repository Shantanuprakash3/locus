CC = gcc
CFLAGS = -g -Wall


default: compiler

compiler: main.o lexer.o adjacencyList.o node.o parser.o tree.o
		  $(CC) $(CFLAGS) -o compiler main.o lexer.o adjacencyList.o node.o parser.o tree.o

main.o: main.c lexer.h adjacencyList.h parser.h tree.h 
	    $(CC) $(CFLAGS) -c main.c -o main.o

lexer.o: lexer.c lexer.h adjacencyList.h
	    $(CC) $(CFLAGS) -c lexer.c -o lexer.o

tree.o: tree.c tree.h parser.h node.h adjacencyList.h parser.h lexer.h
	gcc -c tree.c parser.o adjacencyList.o node.o -o tree.o

parser.o: parser.c parser.h adjacencyList.h node.h
	gcc -c parser.c -o parser.o

adjacencyList.o: adjacencyList.c adjacencyList.h
	gcc -c adjacencyList.c -o adjacencyList.o

node.o: node.c node.h
	gcc -c node.c -o node.o


# parser.o: parser.c lexer.h parser.h
# 	    $(CC) $(CFLAGS) -c parser.c



clean: 
	$(RM) count *.o *~