%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "q4.tab.h"
%}
%%
";" {printf("%s\n",yytext); return SS;}
"'"  {printf("%s\n",yytext); return COM;}
[0-9]+ {printf("%s\n",yytext); return NUM;}
"*" {printf("%s\n",yytext); return MOP;}
"+" {printf("%s\n",yytext); return AOP;}
"/" {printf("%s\n",yytext); return DOP;}
"-" {printf("%s\n",yytext); return SOP;}
"^" {printf("%s\n",yytext); return EOP;}
"N"  {printf("%s\n",yytext); return NOP;}

"\n" {printf("%s\n",yytext); return NL; }
%%
int yywrap()
{
	return 1;
}