#include<stdio.h>
#include<string.h>
#include<ctype.h>
char str[100];
int c=1;
char curr;
int flag=0;
void A();
void B();
void C();
void S();
void S()
{
	if(curr=='a')
	{
		curr=str[c++];
		//printf("%c ",curr);
		A();
		//curr=str[c++];
		if(curr=='c')
		{
			printf("%c ",curr);
			curr=str[c++];
			B();
			//curr=str[c++];
			if(curr=='e')
			{
		//		printf("%c ",curr);
				curr=str[c++];
				if(curr=='$')
					flag=1;
				else
					flag=0;
			}
			else
				flag=0;
		}
		else
			flag=0;
	}
	else
		flag=0;
}
void A()
{
	if(curr=='b')
	{
		curr=str[c++];
		//printf("%c ",curr);
		C();
	}
	else
	{
		printf("Not accepted\n");
		exit(0);
	}
}
void C()
{
	if(curr=='b')
	{
		curr=str[c++];
		//printf("%c ",curr);
		C();
	}
	else
		return;
}
void B()
{
	if(curr=='d')
	{
		curr=str[c++];
		//printf("%c ",curr);
		return;
	}
	else
	{
		printf("Not accepted\n");
		exit(0);
	}
}
void main()
{
	printf("Enter the string\n");
	gets(str);
	curr=str[0];
	//printf("%c ",curr);
	S();
	if(flag==1)
		printf("Accepted\n");
	else
		printf("Not Accepted\n");
}