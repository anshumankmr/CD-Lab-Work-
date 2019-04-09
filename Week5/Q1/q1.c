#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
void print_error()
{
	printf("String doesnt belong to grammar %s\n",lookAhead);
	exit(0);
}
void S();
void T1();
void T() 
{
	printf("In the T %s %d \n",lookAhead ,curr);
	S();
	T1();
}
void T1()
{
	// strcpy(lookAhead,getNextToken());
	printf(" T1 %s\n",lookAhead );
	if (strcmp(lookAhead,",\0")==0)
	{
			strcpy(lookAhead,getNextToken());
		S();
		T1();
	}
	else if (strcmp(lookAhead,"$\0")==0)
	{
		printf("Accepted\n");
		exit(0);
	}
	else
	{
		return;
	}
}
void S() 
{
	if(strcmp(lookAhead, "a\0") == 0 || strcmp(lookAhead, ">\0") == 0) 
	{
		strcpy(lookAhead, getNextToken());
		// strcpy(lookAhead,getNextToken());
		 if(strcmp(lookAhead, "$\0") == 0) 
	     {
		  printf("Successfully parsed..\n");
		  exit(0);
	     }  
	} 
	else if (strcmp(lookAhead, "(\0") == 0) 
	{
		strcpy(lookAhead, getNextToken());
		T();
		strcpy(lookAhead,getNextToken());
		printf("exited T %s %d \n",lookAhead,curr);
		if (strcmp(lookAhead,")\0")==0)
		{
		 strcpy(lookAhead,getNextToken());
		 if(strcmp(lookAhead, "$\0") == 0) 
	     {
		  printf("Successfully parsed\n");
		  exit(0);
	     }  
		}
	}
	// else if(strcmp(lookAhead, "$\0") == 0) 
	// {
	// 	printf("Successfully parsed.\n");
	// 	exit(0);
	// } 
	// else 
	// {
	// 	print_error();
	// }
}



int main() 
{
    init();
    // printf("dfssdfdf\n");
 	strcpy(lookAhead, getNextToken());
	S();
}