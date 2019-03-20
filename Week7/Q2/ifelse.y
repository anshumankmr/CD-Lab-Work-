%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token NL ID EQ OB CB OCB CCB IF ELSE NUM PLUS MINUS LT GT IEQ SC
%%
stmtprime: dec_stmt NL
	;
dec_stmt: IF OB exp CB NL OCB NL stmt_list CCB NL dprime 
	;
dprime: ELSE NL OCB NL stmt_list CCB NL
	| 
	;
stmt_list: stmt stmt_list
	| stmt
	;
stmt: ID EQ exp SC NL
	;
exp: exp PLUS term
	| exp MINUS term
	| term LT term
	| term GT term
	| term IEQ term
	| term
	;
term: ID 
	| NUM
	;
%%
int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	return 1;
}
void main()
{
	printf("Enter the expression\n");
	yyin=fopen("in.txt","r");
	//yyin=stdin;
	do
	{
		if(yyparse())
		{
			printf("\nFailure\n");
			exit(0);
		}
	}
	while(!feof(yyin));
	printf("Success\n");
}