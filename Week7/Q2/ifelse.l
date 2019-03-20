%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "ifelse.tab.h"
%}
%%
\n {printf("%s\n",yytext);return NL;}
"+" {printf("%s\n",yytext);return PLUS;}
"-" {printf("%s\n",yytext);return MINUS;}
"<" {printf("%s\n",yytext);return LT;}
">" {printf("%s\n",yytext);return GT;}
"=" {printf("%s\n",yytext);return EQ;}
"==" {printf("%s\n",yytext);return IEQ;}
[0-9]+ {printf("%s\n",yytext);return NUM;}
\( {printf("%s\n",yytext);return OB;}
\) {printf("%s\n",yytext);return CB;}
\{ {printf("%s\n",yytext);return OCB;}
\} {printf("%s\n",yytext);return CCB;}
"if" {printf("%s\n",yytext);return IF;}
"else" {printf("%s\n",yytext);return ELSE;}

[a-zA-Z]+[0-9]* {printf("%s\n",yytext);return ID;}
";" {printf("%s\n",yytext);return SC;}
%%
int yywrap()
{
	return 1;
}