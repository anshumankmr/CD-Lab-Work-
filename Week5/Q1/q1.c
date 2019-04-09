#include <stdio.h>
#include <string.h>
#include "helper.h"
void S();
void T() 
{
	S();
}
void S() 
{
	if(strcmp(lookAhead, "a\0") == 0 || strcmp(lookAhead, ">\0") == 0) 
	{
		strcpy(lookAhead, getNextToken());
	} 
	else if (strcmp(lookAhead, "(\0") == 0) 
	{
		strcpy(lookAhead, getNextToken());
		T();
	}

	if(strcmp(lookAhead, "EOL\0") == 0) 
	{
		printf("Successfully parsed.");
	} 
	else 
	{
		printf("String doesnt belong to grammar");
		exit(0);
	}
}



int main() 
{
    init();
    // printf("dfssdfdf\n");
 	strcpy(lookAhead, getNextToken());
	S();
}