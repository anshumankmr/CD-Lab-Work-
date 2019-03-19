%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token NL ID NUMBER PLUS MINUS
%left '+' '-'

%% 
stmt: exp NL
	;
exp: exp PLUS term | exp MINUS term | term ; 

term: ID | NUMBER ;
%%

int yyerror(char *msg)
{
	printf("invalid expression\n");
	return 1; 
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("in.txt", "r");
	//yyin=stdin;

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