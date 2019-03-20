#ifndef LEX_H
#define LEX_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 30

FILE *fp;

enum tokenType { ARITH_OP, REL_OP, LOG_OP, SYMBOL, NUM_CONST, STRING, ID, ASSIGN_OP, KEYWORD, CHAR_LITERAL};
struct token {
	char lexeme[MAX_SIZE];
	int rowno;
	int colno;
	enum tokenType type;
};

struct token* createToken() {
	struct token* t = (struct token*) malloc(sizeof(struct token));
	return t;
}

void assignValuesToToken(struct token* t, char* str, int row, int col, enum tokenType type) {
	strcpy(t->lexeme, str);
	t->rowno = row;
	t->colno = col;
	t->type = type;
}

int isNum(char c) {
	return c >= '0' && c <= '9';
}

int isChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isKeyword(char* s) {
	return !(strcmp(s,"for") && strcmp(s,"int") && strcmp(s,"switch") && strcmp(s,"case"));
}

int rowno = 1;
int colno = 0;

struct token* returnToken(struct token* t, char* buff, int i, char c, enum tokenType type) {
	buff[i++] = c;
	buff[i] = '\0';
	assignValuesToToken(t, buff, rowno, colno - strlen(buff) + 1, type);
	return t;
}

struct token* returnAndRetract(struct token* t, char* buff, int i, char c, enum tokenType type, FILE* fp) {
	buff[i] = '\0';
	ungetc(c, fp);
	colno--;
	assignValuesToToken(t, buff, rowno, colno - strlen(buff) + 1, type);
	return t;
}

struct token* getNextToken() {
	char c, buff[10];

	c = fgetc(fp);
	colno++;
	struct token* t = createToken();
	while(c != EOF) {

		int i=0;
		buff[0] = '\0';

		// TODO: Ignore Includes and comments (Preprocess).

		//Relational Operators.
		if(c == '=') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '=') {
				return returnToken(t, buff, i, c, REL_OP);
			} else {
				return returnAndRetract(t, buff, i, c, ASSIGN_OP, fp);
			}
		} else if (c == '<' || c == '>' || c == '!') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '=') {
				return returnToken(t, buff, i, c, REL_OP);
			} else {
				if(buff[0] == '!')
					return returnAndRetract(t, buff, i, c, LOG_OP, fp);
				else
					return returnAndRetract(t, buff, i, c, REL_OP, fp);
			}
		}

		//Logical Operators
		if(c == '&') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '&') {
				return returnToken(t, buff, i, c, LOG_OP);
			} else if(c == '=') {
				return returnToken(t, buff, i, c, ASSIGN_OP);
			} else {
				return returnAndRetract(t, buff, i, c, LOG_OP, fp);
			}
		}

		if(c == '|') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '|') {
				return returnToken(t, buff, i, c, LOG_OP);
			} else if(c == '=') {
				return returnToken(t, buff, i, c, ASSIGN_OP);
			} else {
				return returnAndRetract(t, buff, i, c, LOG_OP, fp);
			}
		}


		if(c == '^') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '=') {
				return returnToken(t, buff, i, c, ASSIGN_OP);
			} else {
				return returnAndRetract(t, buff, i, c, LOG_OP, fp);
			}
		}

		//Arithmetic Op
		if(c == '+' || c == '-' || c == '/' || c == '*') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if((buff[0] == '+' && c == '+') || (buff[0] == '-' && c =='-') || c == '=') {
				return returnToken(t, buff, i, c, ASSIGN_OP);
			} else {
				return returnAndRetract(t, buff, i, c, ARITH_OP, fp);
			}
		}

		// Numeric Constant(only integers and longs)
		if(isNum(c)) {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			while(isNum(c)) {
				buff[i++] = c;
				c = fgetc(fp);
				colno++;
			}
			return returnAndRetract(t, buff, i, c, NUM_CONST, fp);

		}

		//String literal
		if(c == '"') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			while(c != '"') {
				buff[i++] = c;
				c = fgetc(fp);
				colno++;
			}
			return returnToken(t, buff, i, c, STRING);
		}

		if(c == '\'') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			while(c != '\'') {
				buff[i++] = c;
				c = fgetc(fp);
				colno++;
			}
			return returnToken(t, buff, i, c, CHAR_LITERAL);
		}

		//ID
		if(isChar(c)) {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			while(isChar(c) || isNum(c) || c == '_') {
				buff[i++] = c;
				c = fgetc(fp);
				colno++;
			}
			buff[i] = '\0';
			if(isKeyword(buff))
				return returnAndRetract(t, buff, i, c, KEYWORD, fp);
			return returnAndRetract(t, buff, i, c, ID, fp);
		}

		//SYMBOL
		if(c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')' || c == '*' || c == ';' || c == ',' || c == ':') {
			return returnToken(t, buff, i, c, SYMBOL);
		}

		if (c == ' ') {
			colno++;
		}

		if(c == '\t') {
			colno+=4;
		}
		if(c == '\n') {
			rowno++;
			colno=0;
		}

		c = fgetc(fp);
		colno++;
	}
	return 0;
}
#endif