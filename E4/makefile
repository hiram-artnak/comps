CC=gcc
LIBS=-lfl
CFLAGS = -I.
DEPS=lexeme.c linked_list.c ast.c utils.c hash_table.c stack.c symbol.c stack.c parser_utils.c
BISON_DEPS= ast.o stack.o linked_list.o
OBJ = main.o utils.o ast.o linked_list.o lex.yy.o parser.tab.o hash_table.o stack.o symbol.o stack.o parser_utils.o

etapa4: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

parser.tab.o: parser.tab.c parser.tab.h
	$(CC) -c -o $@ $<

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<


parser.tab.c, parser.tab.h: parser.y
	bison -d parser.y -Wcounterexamples 2> counterexamples.txt

lex.yy.c: scanner.l parser.tab.h parser.tab.o
	flex scanner.l

.PHONY: clean

clean:
	rm -f lex.yy.c parser.tab.c *.o etapa3  parser.tab.h counterexamples.txt