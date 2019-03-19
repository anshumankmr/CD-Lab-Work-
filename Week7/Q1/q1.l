%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "q1.tab.h"
%}
%%
";" { printf("%s\n",yytext); return SS;}
"int" {printf("%s\n",yytext); return INT;}
"char" {printf("%s\n",yytext); return CHAR;}
"," {printf("%s\n",yytext); return CO; }
[a-zA-Z]+ {printf("%s\n",yytext); return ID;}

"\n" {printf("NL\n"); return NL; }
%%
int yywrap()
{
	return 1;
}