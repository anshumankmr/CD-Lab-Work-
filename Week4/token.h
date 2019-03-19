#ifndef LEXEME_H
#define LEXEME_H
#define MAX_LEXEME_SIZE 20	
#include<string.h>
struct token {
	char* lexeme;
	int index;
	unsigned int rowno, colno;
	char type[10];
	char retType[10];
	int numArgs;
	int scope;
	int size;
};

struct token* allocToken() {
	struct token* tk;
	tk = (struct token*) malloc(sizeof(struct token));
	tk->lexeme = (char*) malloc(sizeof(char)*MAX_LEXEME_SIZE);
	tk->index = -1;
	// tk->type = EOFILE;
	return tk;
}

void setTokenArgs(struct token* tk, char* lexeme, int index, int rowno, int colno, char* type,int scope, char* retType, int numArgs) {
	if(!tk)
		return;
	strcpy(tk->lexeme, lexeme);
	strcpy(tk->type, type);
	strcpy(tk->retType, retType);
	tk->index = index;
	tk->rowno = rowno;
	tk->colno = colno;
	tk->numArgs = numArgs;
	tk->scope = scope;

}


#endif