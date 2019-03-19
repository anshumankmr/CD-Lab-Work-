%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token INT CHAR SS CO NL ID

%% 
stmt: DC NL ;
DC: DT IDL SS | ;
DT : INT | CHAR ;
IDL : ID | ID CO IDL ;

%%

int yyerror(char *msg)
{
	printf("invalid expression\n");
	return 1; 
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("q1in.txt", "r");
	do 
	{
	if(yyparse())
	{
	printf("\n Failure");
	exit(0);
	}
	} while (!feof(yyin));
	printf("success");
}