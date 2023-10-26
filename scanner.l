/* scanner.l 
 * A lexical analyzer for the class project for INF01147 Compilers course
 * Authors: Bibiana and Hiram
 * Date: 2023, October
 */

  /* Options */


  /* yywrap is useless and better handled by other IO functions. */
%option noyywrap

  /* Automatically count lines (required by the specification) */
%option yylineno

  /*The default rule is bad to us, so we disable it*/ 


  /* C code */
%{
  /*Tokens are defined in tokens.h by the professor*/
  #include "tokens.h"
  #include <stdio.h>
  /* It is our responsibility to initialize yylineno*/


  int get_line_number();
%}

  /* Substitution rules */
DIG [0-9]
LETTER [a-zA-Z]
SPECIAL [!*\/%+\\\-<>{}()=,;]
SPACE " "

  /* States */
%x COMMENT

%%
  /* Rules */
  /* Comments */
  /* Multi-line comments*/
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>. { /* ignore */ }

  /* Single-line comments*/
"//"(.)* { /* ignore */ }

  /* Whitespace */
{SPACE} { /* ignore */ }

  /* Reserved words */
"int" {fprintf(stderr, ":: int"); return TK_PR_INT;}
"float" { fprintf(stderr, ":: float");return TK_PR_FLOAT;}
"bool" { fprintf(stderr, ":: bool");return TK_PR_BOOL;}
"if" { fprintf(stderr, ":: if");return TK_PR_IF;}
"else" { fprintf(stderr, ":: else");return TK_PR_ELSE;}
"while" { fprintf(stderr, ":: while");return TK_PR_WHILE;}
"return" { fprintf(stderr, ":: return");return TK_PR_RETURN;}

  /* Literals */
"false" { fprintf(stderr, ":: false");return TK_LIT_FALSE;}
"true" { fprintf(stderr, ":: true");return TK_LIT_TRUE;}
{DIG}+ { fprintf(stderr, ":: INT Lit");return TK_LIT_INT;}
{DIG}?\.{DIG}+ { fprintf(stderr, ":: FLOAT");return TK_LIT_FLOAT;}

  /* Composite Operators */
"<=" { fprintf(stderr, ":: <=");return TK_OC_LE;}
">=" { fprintf(stderr, ":: >=");return TK_OC_GE;}
"==" { fprintf(stderr, ":: ==");return TK_OC_EQ;}
"!=" { fprintf(stderr, ":: !=");return TK_OC_NE;}
"&" { fprintf(stderr, ":: &");return TK_OC_AND;}
"|" { fprintf(stderr, ":: or");return TK_OC_OR;}

  /* Identifiers */
({LETTER}|_)({LETTER}|{DIG}|"_")* { fprintf(stderr, ":: id %s", yytext); return TK_IDENTIFICADOR;}

{SPECIAL} { fprintf(stderr, ":: %c", yytext[0]);return yytext[0]; }

\n {}

. {return TK_ERRO;}

%%

int get_line_number(){
  return yylineno; 
}

int main(){
  while(yylex()){
    fprintf(stderr, "\t%d\n", get_line_number());
  }
}
/* End of the file */
