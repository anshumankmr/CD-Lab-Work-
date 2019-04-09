%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "token.h"
	#include "table.h"
	#define YY_DECL struct token* yylex(void)

	int lineno = 1, colno=1;
	int scope = 0;
	struct token* tk;

%}

%%
"/*"(.|\n)*"*/" {
	int i=0;
	while(yytext[i] != '\0') {
		if(yytext[i] == '\n') {
			lineno++;
			colno=1;
		} else {
			colno++;
		}
		i++;
	}
}

"//".*"\n" { lineno++; colno=1;}

(\"(.)*\") {colno += strlen(yytext);}

(\'(.)*\') {colno += strlen(yytext);}


int|for|float|double|char|if|else|switch|case|for|while|do|short|long|exit {
	//Ignore keywords
	tk = allocToken();

}

(int|float|double|char|short|long|void)[ ]+[a-zA-Z][a-zA-Z0-9_]* {
	//get variables
	tk = allocToken();
	char retType[3] = "NA\0";
	char type[10],lexeme[1000];
	int flag = 0 , k  = 0 ;
  for (int i = 0 ; i< strlen(yytext);i++)
	{
   if (yytext[i]!=' ' && flag == 0  )
	 {
	  type[k++]=yytext[i];
	 }
	 if ( yytext[i]==' ' && flag == 0)
	 {
	  type[k]='\0';
		flag = 1;
		k =0 ;
	 }
	 if (yytext[i]!=' ' && flag == 1  )
	 {
	  lexeme[k++]=yytext[i];
	 }
	}
	setTokenArgs(tk, lexeme, -1, lineno, colno, type,scope, retType, -1);
	colno+=strlen(yytext);
	insert(*tk);
}

\{ {
	scope++;
}

\} {
	scope--;
}

(int|float|double|char|short|long|void)[ ]+[a-zA-Z][a-zA-Z0-9_]*[ ]*\(.*\) {

	tk = allocToken();
	char retType[10];
	int numArgs = 1;

	// Get return type
	for(int i=0;i<strlen(yytext);i++) {
		if(yytext[i] == ' ') {
			retType[i] = '\0';
			break;
		}
		retType[i] = yytext[i];
	}

	// Get lexeme
	char lexeme[20];
	for(int i=0;i<strlen(yytext);i++) {
		int k = 0;
		if(yytext[i] == ' ') {
			int j = i+1;
			while(yytext[j] == ' ') j++;
			while(yytext[j] != ' ' && yytext[j] != '(')
				lexeme[k++] = yytext[j++];
			lexeme[k] = '\0';
			break;
		}
	}

	//TODO: Improve the logic
	for(int i=0;i<strlen(yytext);i++) {
		if(yytext[i] == '(') {
			for(int j=i+1;j<strlen(yytext); j++) {
				if( yytext[j] == ',') numArgs++;
			}
			break;
		}
	}
	setTokenArgs(tk, lexeme, -1, lineno, colno, "FUNC\0",scope, retType, numArgs);
	colno+=strlen(yytext);
	insert(*tk);
}

\n {lineno++; colno=1;}

"\t" {colno += 4;}

. { colno++; }
%%

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Requires name of a C file. \n");
		exit(1);
	}

	yyin = fopen(argv[1], "r");

	int count = 0;
	init();
	yylex();

	return 0;
}

int yywrap() {
	display();
	return 1;
}
