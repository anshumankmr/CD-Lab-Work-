#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>
#include "helper.h"
void E();
void E1();
void T();
void T1();
void F();
void E()
{
 T();
 E1();
}
void E1()
{
	if (strcmp(string,"+\0")==0)
	{
		strcpy(string,getNextToken());
		T();
	}
	else if (strcmp(string,"$\0")==0)
	{
      printf("Accepted\n");
      exit(0);
	}
	// else
	// {
	// 		printf("UnAccepted\n");
	// 		exit(0);

	// }
}
void T()
{
	F();
	T1();
}
void T1()
{
  if (strcmp(string,"*\0")==0)
	{
		// printf("asdsffdsfdffddsf\n");
		strcpy(string,getNextToken());
		F();
	}
	else if (strcmp(string,"$\0")==0)
	{
      printf("Accepted\n");
      exit(0);
	}
	// else
	// {
	// 		printf("not Accepted\n");
	// 		exit(0);
	// }
}
void F()
{
	if (strcmp(string,"(\0")==0)
	{
		strcpy(string,getNextToken());
		E();
		strcpy(string,getNextToken());//
		if (strcmp(string,")\0")==0)
	    {
		 strcpy(string,getNextToken());
		 if (strcmp(string,"$\0")==0)
     	 {
          printf("Accepted\n");
          exit(0);
	     }
	    }
	}
	else if (toupper(string[0])>='A' || toupper(string[0])<='Z')
	{
		int i = 1,flag=1;
		for (i = 1; i < strlen(string);i++)
		{
			if (!( toupper(string[i])>='A' || toupper(string[i])<='Z' || (string[i])>='0' || (string[i])<='9' || string[i]=='_'))
			{
             flag = 0;
			}
		}
		if (flag == 1)
		{
			strcpy(string,getNextToken());
		 if (strcmp(string,"$\0")==0)
     	 {
          printf("Accepted\n");
          exit(0);
	     }
		}
	}
}
int main()
{
	init();
	strcpy(string,getNextToken());
	E();
	printf("Not Accepted\n");
}