%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define MAX_LEXEME_SIZE 20
	#define YY_DECL struct token* yylex(void)
	enum tokenType {EOFILE=-1, LESS_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN, GREATER_THAN_OR_EQUAL, EQUAL, NOT_EQUAL, KEYWORD, ID, PLUS, MINUS, MULT, DIV, LOG_AND, LOG_OR, BIT_AND, BIT_OR, EXOR, ASSIGN};

	struct token {
		char* lexeme;
		int index;
		unsigned int rowno, colno;
		enum tokenType type;
	};

	int lineno = 1, colno=1;
	
	struct token* tk;

	struct token* allocToken() {
		struct token* tk;
		tk = (struct token*) malloc(sizeof(struct token));
		tk->lexeme = (char*) malloc(sizeof(char)*MAX_LEXEME_SIZE);
		tk->index = -1;
		tk->type = EOFILE;
		return tk;
	}

	void setTokenArgs(struct token* tk, char* lexeme, int index, int rowno, int colno, enum tokenType type) {
		if(!tk)
			return;
		tk->lexeme = lexeme;
		tk->index = index;
		tk->rowno = rowno;
		tk->colno = colno;
		tk->type = type;
	}
%}

%%
"#".*"\n" {
	lineno++;
	colno = 1;
}

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

(auto|double|int|struct) |
(break|else|long|switch) |
(case|enum|register|typedef) |
(char|extern|return|union) |
(const|float|short|unsigned) |
(continue|for|signed|void) |
(default|goto|sizeof|volatile) |
(do|if|static|while) {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, KEYWORD);
	colno+=strlen(yytext);
	return tk;
}

[_a-zA-Z][a-zA-Z0-9_]* {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, ID);
	colno+=strlen(yytext);
	return tk;	
}

\n {lineno++; colno=1;}

"<" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, LESS_THAN);
	colno++;
	return tk;
}

"<=" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, LESS_THAN_OR_EQUAL);
	colno+=2;
	return tk;
}

">" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, GREATER_THAN);
	colno++;
	return tk;
}

">=" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, GREATER_THAN_OR_EQUAL);
	colno+=2;
	return tk;
}

"==" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, EQUAL);
	colno+2;
	return tk;
}

"+" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, PLUS);
	colno+=1;
	return tk;
}

"-" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, MINUS);
	colno+=1;
	return tk;
}

"*" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, MULT);
	colno+=1;
	return tk;
}

"/" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, DIV);
	colno+=1;
	return tk;
}

"&&" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, LOG_AND);
	colno+=2;
	return tk;
}

"||" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, LOG_OR);
	colno+=2;
	return tk;
}

"&" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, BIT_AND);
	colno+=1;
	return tk;
}

"|" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, BIT_OR);
	colno+=1;
	return tk;
}

"^" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, EXOR);
	colno+=1;
	return tk;
}

"!=" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, NOT_EQUAL);
	colno+=2;
	return tk;
}

"=" {
	tk = allocToken();
	setTokenArgs(tk, yytext, -1, lineno, colno, ASSIGN);
	colno+=1;
	return tk;
}


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

	while(tk = yylex()) {
		printf("%d %d %d %s %d\n", count, tk->rowno, tk->colno, tk->lexeme, tk->type);
		count++;
	}

	return 0;
}

int yywrap() {
	return 1;
}



