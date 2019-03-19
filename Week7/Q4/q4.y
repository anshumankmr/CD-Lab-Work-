%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token SS NL MOP SOP DOP AOP NUM EOP COM NOP

%% 
stmt: IP NL ;
IP : IP LINE | ;
LINE : NL | EXP NL;
COMMA : COM OPE COM;
OPE :  MOP | SOP | AOP | DOP | NOP | EOP;
EXP : EXP EXP COMMA | NUM;
%%

int yyerror(char *msg)
{
	printf("invalid expression\n");
	return 1; 
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("q4in.txt", "r");
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