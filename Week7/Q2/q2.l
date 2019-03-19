%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "q2.tab.h"
%}
%%
";" {printf("%s\n",yytext); return SS;}
"" {printf("%s\n",yytext); return ;}
"" {printf("%s\n",yytext); return ;}
"" {printf("%s\n",yytext); return ;}
[a-zA-Z]+ {printf("%s\n",yytext); return ID;}

"\n" {printf("NL\n"); return NL; }
%%
int yywrap()
{
	return 1;
}