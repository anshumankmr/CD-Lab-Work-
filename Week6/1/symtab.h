#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define tableLen 509

enum tokenType {EOFILE=-1, LITERAL, KEYWORD, NUMBER, IDENTIFIER, SYMBOL, AOP, LOP, RELOP};

struct Token
{
	char *lexeme;
	int index;
	int row, col;
	enum tokenType type;
};
typedef struct Token* Tokenptr;

struct ListElement
{
	Tokenptr tp;
	int hashval, argc;
	char name[10], type[10], scope, args[10][100], ret[10], func[10];
	struct ListElement *next;
};
typedef struct ListElement* LEptr;

LEptr TABLE[tableLen];

void initialize()
{
	for(int i=0; i<tableLen; i++)
		TABLE[i] = NULL;
}

void Display()
{
	printf("HASH\tID/FUNC\t\tNAME\tTYPE\tSCOPE\tRET\tARG C\tARGS\n");
	for(int i=0; i<tableLen; i++)
	{
		LEptr temp = TABLE[i];
		while(temp)
		{
			printf("%d\t%s\t%s\t%s\t%c\t%s\t", temp -> hashval, temp -> func, temp -> name, temp -> type, temp -> scope, temp -> ret);
			if(strcmp(temp -> func, "FUNCTION")==0)
				printf("%d\t", temp -> argc);
			for(int i = 0; i<temp ->argc; i++)
			{
				printf("%s", temp -> args[i]);
				if(i!=temp->argc-1)
					printf(", ");
			}
			printf("\n");
			temp = temp->next;
		}
	}
}

int Hash(char *str)
{
	int s=0, p=31, pw=1;
	for(int i=0; i<strlen(str); i++)
	{
		s = (s + (str[i])*pw) %tableLen;//-'a'+1
		pw = (pw*p)%tableLen;
	}
	return s;
}

int Search(char *str)
{
	int x = Hash(str);
	LEptr temp = TABLE[x];
	while(temp)
	{
		if(strcmp(temp->tp->lexeme, str)==0)
			return 1;
		temp = temp->next;
	}
	return 0;
}

int Insert(Tokenptr tp, int func, char* dtype, int scope, char args[10][100], int argc)
{
	if(Search(tp->lexeme)==1)
		return Hash(tp->lexeme);
	int x = Hash(tp->lexeme);
	// printf("%d\n", x);
	LEptr le = (LEptr)malloc(sizeof(struct ListElement));
	le -> tp = tp;
	strcpy(le -> name, tp->lexeme);
	le -> hashval = x;
	if(func == 0)
	{
		strcpy(le -> func, "IDENTIFIER");
		le -> argc = 0;
		le -> ret[0] = '\0';
		if(scope == 0)
			le -> scope = 'G';
		else
			le -> scope = 'L';
		strcpy(le -> type, dtype);
	}
	else if(func == 1)
	{
		strcpy(le -> func, "FUNCTION");
		le -> scope = ' ';
		le -> type[0] = '\0';
		strcpy(le -> ret, dtype);
		if(le -> ret[0] == '\0')
			strcpy(le -> ret, "void");
		le -> argc = argc;
		for(int i=0; i<argc; i++)
			strcpy(le -> args[i], args[i]);
	}
	le -> next = NULL;
	if(TABLE[x]==NULL)
		TABLE[x] = le;
	else
	{
		LEptr temp = TABLE[x];
		x += tableLen;
		while(temp->next)
		{
			temp = temp->next;
			x += tableLen;
		}
		// temp -> hashval = x;
		temp->next = le;
	}
	return x;
}
//name, type, size, scope, no of args, args, ret type