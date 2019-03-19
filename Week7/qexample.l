%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "a.tab.h"
%}
%%
[0-9]+ {printf("%s\n",yytext); return NUMBER;}
\n {return NL;}
[a-zA-Z]+ {printf("%s\n",yytext); return ID:}
"+" {printf("PLUS\n"); return PLUS; }
"+" {printf("MINUS\n"); return MINUS; }
%%
int yywrap()
{
	return 1;
}