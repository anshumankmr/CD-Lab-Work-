#include<stdio.h>
#include<string.h>
#include<ctype.h>
char str[100];
int c=1;
char curr;
int flag=0;
void E();
void Y();
void T();
void Z();
void F();
void E()
{
	T();
	Y();
	if(curr=='$')
		flag=1;
	else
		flag=0;
	return;
}
void Y()
{
	if(curr=='+')
	{
		curr=str[c++];
		T();
		Y();
	}
	else
		return;
}
void T()
{
	F();
	Z();
}
void Z()
{
	if(curr=='*')
	{
		curr=str[c++];
		F();
		Z();
		return;
	}
	else
		return;
}
void F()
{
	if(curr=='(')
	{
		curr=str[c++];
		E();
		if(curr==')')
		{	
			curr=str[c++];
			if(curr=='$')
				flag=1;
			else
				flag=0;
		}
		else
		{
			printf("Not Accepted\n");
			exit(0);
		}
	}
	else if(isalpha(curr))
	{
		while(curr!='$'&&(isalnum(curr)||curr=='_'))
			curr=str[c++];
	}
	else
	{
		printf("Not accepted\n");
		exit(0);
	}
	if(curr=='$')
		flag=1;
	else
		flag=0;
}
void main()
{
	printf("Enter the string\n");
	gets(str);
	curr=str[0];
	E();
	if(flag==1)
		printf("Accepted\n");
	else
		printf("Not Accepted\n");
}