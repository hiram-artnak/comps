run:
	flex scanner.l ; gcc ./main.c ./lex.yy.c -o analisador -lfl;
