#include "lex.yy.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Tokenptr tk;
Tokenptr getNextToken()
{
	Tokenptr tp;
	if(!(tp=yylex()))
		tp=NULL;

	return tp;
}

int loc=0;

void factor();
void switch_st();
void casest();
void cases();
void brk1();
void dft();
void A();

void reject()
{
	printf("Error in line %d %s\n",tk->row,tk->lexeme);
	exit(0);
}
void Accept()
{
	printf("Accept\n");
	exit(0);
}

void switch_st()
{
	if(tk && strcmp(tk->lexeme,"switch")==0)
	{
		tk= getNextToken();
		if(tk && strcmp(tk->lexeme,"(")==0)
		{
			tk=getNextToken();
			factor();
			
			if(tk && strcmp(tk->lexeme,")")==0)
			{
				tk= getNextToken();
				if(tk && strcmp(tk->lexeme,"{")==0)
				{
					tk=getNextToken();
					casest();
					dft();

					if(tk && strcmp(tk->lexeme,"}")==0)
						tk= getNextToken();
					else
						reject();

					if(tk && strcmp(tk->lexeme,"$")==0)
						Accept();
					else
						reject();
				}
				else
				{
					reject();
				}
			}
			else
				reject();
		}
		else
			reject();
	}
	else
		reject();
}

void casest()
{
	if(tk && strcmp(tk->lexeme,"case")==0)
	{
		cases();
		casest();
	}
}

void cases()
{
	if(tk && strcmp(tk->lexeme,"case")==0)
	{
		tk= getNextToken();
		A();

		if(tk && strcmp(tk->lexeme,":")==0)
		{
			loc=0;
			tk=getNextToken();
			
			while(1)
			{
				tk= getNextToken();

				if(tk && strcmp(tk->lexeme,"break")==0)
					break;
				// else if(tk && strcmp(tk->lexeme,"{")==0)
				// 	loc++;
				// else if(tk && strcmp(tk->lexeme,"}")==0)
				// 	loc--;
				// else
				// 	continue;			
			}
			brk1();
			printf("in cases after brk\n");
	
		}
		else
			reject();
	}
	else
		reject();
}
void A()
{
	printf("in A\n");
	
	if(tk && (tk->type == NUMBER))
	{
		tk=getNextToken();
		//printf("factor a\n");
	}
	else if(strcmp(tk->lexeme,"'")==0){
		//printf("1\n");
		tk=getNextToken();
		//printf("2\n");
		printf("%d\n",strlen(tk->lexeme));
		if(strlen(tk->lexeme)==1){
			printf("3\n");
			tk=getNextToken();
		}
		else
			reject();
		if(strcmp(tk->lexeme,"'")==0){
			tk=getNextToken();
		}
		else
			reject();	
	}
	else
		reject();			
}

void dft()
{
	if(tk && strcmp(tk->lexeme,"default")==0)
	{
		if(tk && strcmp(tk->lexeme,":")==0)
		{	
			loc=0;
			tk=getNextToken();
			
			while(1)
			{
				tk= getNextToken();

				if(tk && strcmp(tk->lexeme,"break")==0)
					break;
				// else if(tk && strcmp(tk->lexeme,"{")==0)
				// 	loc++;
				// else if(tk && strcmp(tk->lexeme,"}")==0)
				// 	loc--;
				// else
				// continue;			
			}
			brk1();
		}
		else
			reject();
	}
	
}
void brk1()
{
	if(tk && strcmp(tk->lexeme,"break")==0)
	{
		tk= getNextToken();
		if(tk && strcmp(tk->lexeme,";")==0)
		{
			tk= getNextToken();
		}
		else
			reject();

	}
	else
		reject();
}
void factor()
{
	// /printf("%s\n",tk->lexeme);
	if(tk && (tk->type == IDENTIFIER || tk->type == NUMBER))
	{
		tk=getNextToken();
		//printf("factor a\n");
	}
	else
		reject();
}


int main()
{
	yyin= fopen("input1.c","r");
	tk=getNextToken();
	switch_st();
	//printf("reject\n");
}
