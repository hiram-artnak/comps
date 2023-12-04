CC=gcc
LIBS=-lfl
CFLAGS = -I.
DEPS=lexeme.c llist.c ast.c
BISON_DEPS= lexeme.o ast.o llist.o
OBJ = main.o lexeme.o ast.o llist.o lex.yy.o parser.tab.o

etapa3: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

parser.tab.o: parser.tab.c parser.tab.h
	$(CC) -c -o $@ $<

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<


parser.tab.c, parser.tab.h: parser.y
	bison -d parser.y -Wcounterexamples 2> counterexamples.txt

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean

clean:
	rm -f lex.yy.c parser.tab.c *.o etapa3  parser.tab.h counterexamples.txt