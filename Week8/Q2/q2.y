%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token SS INT CHAR FLOAT TAB NL MAIN CASE BREAK VOID WHILE SWITCH DEFAULT IF ELSE NUM ID ASGN LE GE EQ NE GT  LT PLUS MINUS MULOP DIV OB CB OCB CCB OSB CSB CO MOD FOR

%% 
stmt : program NL;
program: MAIN OB CB OCB declarations statementlist CCB;
declarations: datatype identifierlist SS declarations|;  
datatype:  INT | CHAR |FLOAT;
identifierlist:  ID | ID CO identifierlist | ID OSB NUM CSB CO identifierlist | ID OSB NUM CSB;
statementlist : statement statementlist | ;  
statement : assignstat SS |  decisionstat |  loopingstat;
assignstat : ID ASGN expn;
expn : simpleexpn eprime;
eprime : relop simpleexpn|;
simpleexpn : term seprime ;
seprime: addop term seprime |;
term : factor tprime;
tprime : mulop factor tprime |;
factor : ID | NUM ;
decisionstat : IF OB expn CB OCB statementlist CCB dprime;
dprime : ELSE OCB statementlist CCB | ;
loopingstat : WHILE OB expn CB OCB statementlist CSB | FOR OB assignstat SS expn SS assignstat CB OCB statementlist CCB ;
relop : EQ | NE | LE | GE | LT | GT;
addop :  PLUS |  MINUS ;
mulop : MULOP  | DIV   | MOD;

%%

int yyerror(char *msg)
{
	printf("invalid expression\n");
	return 1; 
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("q2in.txt", "r");
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