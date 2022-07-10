objects = parser.o scanner.o symboltable.o syntaxtree.o main.o
CC = gcc
LEX = flex
YACC = bison

all: pl1c

pl1c: $(objects)
	$(CC) -o $@ $^

parser.c: parser.y
	$(YACC) -d $< -o $@

scanner.c: scanner.l
			$(LEX) -t $< > $@

scanner.o: parser.h
symboltable.o: symboltable.h
parser.o: parser.h symboltable.h syntaxtree.h
main.o: parser.h symboltable.h

clean:
	rm *.o pl1c parser.c scanner.c parser.h *_outC.pl1
