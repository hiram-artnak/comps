CC=gcc
LIBS=-lfl
DEPS=tokens.h
OBJ=main.o  lex.yy.o 

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<

etapa1: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)


lex.yy.c: scanner.l
	flex scanner.l


.PHONY: clean

clean:
	rm -f lex.yy.c *.o etapa1
