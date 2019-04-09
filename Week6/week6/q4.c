#include "lex.yy.c"
#include <stdio.h>
#include <string.h>

void lexp();
void aterm();
void list();
void lexp_seq();
void lexp_seq1();

Tokenptr tk;

Tokenptr getNextToken()
{
	Tokenptr tp;
	if(!(tp = yylex()))
		tp = NULL;
	return tp;
}

void lexp()
{
	if(tk->type == NUMBER || tk->type == IDENTIFIER)
	{
		aterm();
	}
	else if(strcmp(tk->lexeme, "(")==0)
	{
		list();
	}
	else
	{
		printf("Reject\n");
		exit(0);
	}
	tk = getNextToken();
	if(tk == NULL)
	{
		printf("Accept\n");
		exit(0);
	}
}

void aterm()
{
	if(tk->type == NUMBER || tk-> type == IDENTIFIER)
	{
		return;
	}
	else
	{
		printf("Reject\n");
		exit(0);
	}
}

void list()
{
	if(strcmp(tk->lexeme, "(")==0)
	{
		tk = getNextToken();
		lexp_seq();
		if(strcmp(tk->lexeme, ")")==0)
		{
			return;
		}
		else
		{
			printf("Reject\n");
			exit(0);
		}
	}
	else
	{
		printf("Reject\n");
		exit(0);
	}
}

void lexp_seq()
{
	lexp();
	lexp_seq1();
}

void lexp_seq1()
{
	if(strcmp(tk->lexeme, ")")==0)
		return;
	lexp();
	lexp_seq1();
}

int main()
{
	yyin = fopen("ip4.c", "r");
	tk = getNextToken();
	lexp();
	printf("Reject\n");
}