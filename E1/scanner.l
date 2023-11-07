/* scanner.l 
 * A lexical analyzer for the class project for INF01147 Compilers course
 * Authors: Bibiana and Hiram
 * Date: 2023, October
 */

  /* Options */


  /* yywrap is useless and better handled by other IO functions. */
 // %option noyywrap
 // OK I WILL KEEP IT IN CAUSE I DONT KNOW WHAT YOUR MAIN FUNC IS DOING!!!
 // BUT LET IT BE KNOWN
 // I DO IT UNDER PROTEST

  /* Automatically count lines (required by the specification) */
%option yylineno



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
"int" { return TK_PR_INT;}
"float" { return TK_PR_FLOAT;}
"bool" { return TK_PR_BOOL;}
"if" { return TK_PR_IF;}
"else" { return TK_PR_ELSE;}
"while" { return TK_PR_WHILE;}
"return" { return TK_PR_RETURN;}

  /* Literals */
"false" { return TK_LIT_FALSE;}
"true" { return TK_LIT_TRUE;}
{DIG}+ { return TK_LIT_INT;}
{DIG}?\.{DIG}+ { return TK_LIT_FLOAT;}

  /* Composite Operators */
"<=" { return TK_OC_LE;}
">=" { return TK_OC_GE;}
"==" { return TK_OC_EQ;}
"!=" { return TK_OC_NE;}
"&" { return TK_OC_AND;}
"|" { return TK_OC_OR; }

  /* Identifiers */
({LETTER}|_)({LETTER}|{DIG}|"_")* { return TK_IDENTIFICADOR;}

{SPECIAL} { return yytext[0]; }

\n {}

. {return TK_ERRO;}

%%

int get_line_number(){
  return yylineno; 
}

/* End of the file */
