#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *tokens[1000];
char input[8000];
int count=0;
char string[80];
int i;
void init()
{
 printf("Enter the string\n");
 gets(input);
 char * p = strtok(input," ");
 i = 0;
 do
 {
  tokens[i++]=p;
  p =strtok(NULL," ");
 }while(p);
}
char* getNextToken()
{
	if (count+1 <= i)
	{
	 printf("%d %s \n",count, tokens[count] );
	 return tokens[count++];
	}
	else
	{
		printf("Not Accepted\n");
		exit(0);
	}
}