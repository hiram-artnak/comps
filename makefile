CC=gcc
LIBS=-lfl
CFLAGS = -I.
DEPS= lex.yy.c parser.tab.h parser.tab.c
OBJ=main.o  parser.tab.o lex.yy.o

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $<

etapa2: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

parser.tab.c: parser.y 
	bison -d parser.y

lex.yy.c: scanner.l
	flex scanner.l


.PHONY: clean

clean:
	rm -f lex.yy.c parser.tab.c *.o etapa2 
