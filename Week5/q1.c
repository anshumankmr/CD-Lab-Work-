#include<stdio.h>
#include<string.h>
#include<ctype.h>
char str[100];
int c=1;
char curr;
int flag=0;
void S();
void T();
void U();
void S()
{
	if(curr=='a'||curr=='>')
	{
		curr=str[c++];
		if(curr=='$')
			flag=1;
		else
			flag=0;
		return;
	}
	else if(curr=='(')
	{
		curr=str[c++];
		T();
		if(curr==')')
		{
			curr=str[c++];
			if(curr=='$')
				flag=1;
			else
				flag=0;
			return;
		}
	}
	else if(curr=='$')
	{
		flag=1;
		return;
	}
	flag=0;
	return;
}
void T()
{
	S();
	U();
}
void U()
{
	if(curr==',')
	{
		curr=str[c++];
		S();
		U();
	}
	else if(curr=='$')
		return;
	else
		return;
}
void main()
{
	printf("Enter the string\n");
	gets(str);
	curr=str[0];
	S();
	if(flag==1)
		printf("Accepted\n");
	else
		printf("Not Accepted\n");
}