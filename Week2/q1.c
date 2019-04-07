#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 30

enum tokenType { ARITH_OP, REL_OP, LOG_OP, SYMBOL, NUM_CONST, STRING, ID};
struct token 
{
	char lexeme[MAX_SIZE];
	int rowno;
	int colno;
	enum tokenType type;
};

struct token* createToken() 
{
	struct token* t = (struct token*) malloc(sizeof(struct token));
	return t;
}

void assignValuesToToken(struct token* t, char* str, int row, int col, enum tokenType type) 
{
	strcpy(t->lexeme, str);
	t->rowno = row;
	t->colno = col;
	t->type = type;
}

int isNum(char c) 
{
	return c >= '0' && c <= '9';
}

int isChar(char c) 
{	
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int rowno = 1;
int colno = 0;

struct token* returnToken(struct token* t, char* buff, int i, char c, enum tokenType type) 
{
	buff[i++] = c;
	buff[i] = '\0';
	assignValuesToToken(t, buff, rowno, colno - strlen(buff) + 1, type);
	return t;
}

struct token* returnAndRetract(struct token* t, char* buff, int i, char c, enum tokenType type, FILE* fp) 
{
	buff[i] = '\0';
	ungetc(c, fp);
	colno--;
	assignValuesToToken(t, buff, rowno, colno - strlen(buff) + 1, type);
	return t;
}

struct token* getNextToken(FILE *fp) 
{
	char c, buff[1000];

	c = fgetc(fp);
	colno++;
	struct token* t = createToken();
	while(c != EOF) {

		int i=0;
		buff[0] = '\0';

		//Relational Operators.
		if(c == '=') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '=') {
				return returnToken(t, buff, i, c, REL_OP);
			} else {
				return returnAndRetract(t, buff, i, c, REL_OP, fp);
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
				return returnToken(t, buff, i, c, LOG_OP);
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
				return returnToken(t, buff, i, c, LOG_OP);
			} else {
				return returnAndRetract(t, buff, i, c, LOG_OP, fp);
			}
		}


		if(c == '^') {
			buff[i++] = c;
			c = fgetc(fp);
			colno++;
			if(c == '=') {
				return returnToken(t, buff, i, c, LOG_OP);
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
				return returnToken(t, buff, i, c, ARITH_OP);
			} else {
				return returnAndRetract(t, buff, i, c, ARITH_OP, fp);
			}
		}

		// Numeric Constant
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

		//String
		if(c == '"') {
			// printf("why this o\n");
			buff[i++] = c;
			// printf("why this no\n");
			c = fgetc(fp);
			// printf("why this go\n");
			colno++;
			do
			{
				buff[i++] = c;
				// printf("inside loop %c",c);
				c = fgetc(fp);
				colno++;
			}while(c != '"') ;
			return returnToken(t, buff, i, c, STRING);
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
			return returnAndRetract(t, buff, i, c, ID, fp);
		}

		//SYMBOL
		if(c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')' || c == '*' || c == ';' || c == ',') {
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
		}

		c = fgetc(fp);
		colno++;
	}
	return 0;
}

int main(int argc, char** argv ) {
	// if(argc < 2) {
	// 	printf("File name not given.\n");
	// 	exit(1);
	// }
	FILE *fp = fopen("input.c", "r");
	struct token* t;
	while(t = getNextToken(fp)) {
		printf("<%s, %d, %d, %d>\n", t->lexeme, t->rowno, t->colno, t->type);
	}
	return 0;
}
