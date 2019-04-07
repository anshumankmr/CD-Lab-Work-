%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token NUM ID NL I EL OB CB OCB CCB EE NE LTE GTE GT LT SC EQ
%left '+' '-' '*' '\\' '%'

%%
s:dc NL {
	printf("Valid\n");
}
	;

stmt: assign SC
	| dc
	;

assign: ID EQ expn

dc:I OB expn CB newl OCB newl stmt_list newl CCB newl dprime
	;

newl: NL
	|
	;

dprime: EL newl OCB newl stmt_list newl CCB
	|
	;

stmt_list: stmt stmt_list
	|
	;

expn: simexpn eprime
	;

simexpn: term seprime
	;

term: factor tprime
	;

factor: ID
	| NUM
	;

tprime: mulop factor tprime
	|
	;

mulop: '*'
	| '/'
	| '%'
	;

seprime: addop term seprime
	|
	;

addop: '+'
	| '-'
	;

eprime: relop simexpn
	|
	;

relop: EE
	| NE
	| LTE
	| GTE
	| GT
	| LT
	;

%%

int yyerror(char *msg) {
	printf("Invalid\n");
	exit(0);
}

void main() {
	yyin = fopen("q2.txt", "r");
	while(!feof(yyin)) {
		if(yyparse())
			exit(0);
	}
}

