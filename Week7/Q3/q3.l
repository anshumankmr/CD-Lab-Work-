%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "q3.tab.h"
%}
%%
";" {printf("%s\n",yytext); return SS;}
[0-9]+ {printf("%s\n",yytext); return NUM;}
"*" {printf("%s\n",yytext); return MOP;}
"+" {printf("%s\n",yytext); return AOP;}
"/" {printf("%s\n",yytext); return DOP;}
"-" {printf("%s\n",yytext); return SOP;}
[a-zA-Z]+ {printf("%s\n",yytext); return ID;}

"\n" {printf("%s\n",yytext); return NL; }
%%
int yywrap()
{
	return 1;
}