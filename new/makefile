CC=gcc
LIBS=-lfl
CFLAGS = -I.
DEPS=linked_list.c ast.c
BISON_DEPS=ast.o linked_list.o
OBJ = main.o ast.o linked_list.o lex.yy.o parser.tab.o

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