%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token SS NL MOP SOP DOP AOP NUM ID

%% 
stmt: SIMP_EXP NL ;
SIMP_EXP : TERM SEPR;
SEPR : OPE TERM SEPR | ;
OPE :  MOP | SOP | AOP | DOP ;
TERM: ID | NUM;
%%

int yyerror(char *msg)
{
	printf("invalid expression\n");
	return 1; 
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("q3in.txt", "r");
	do 
	{
	 if(yyparse())
	 {
	  printf("\n Failure");
	  exit(0);
	 }
	} while (!feof(yyin));
	printf("Success");
}