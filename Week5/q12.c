#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dummylex.h"

void S() {
	if(strcmp(lookAhead, "a\0") == 0 || strcmp(lookAhead, ">\0") == 0) {
		strcpy(lookAhead, getNextToken());
	} else if (strcmp(lookAhead, "(\0") == 0) {
		strcpy(lookAhead, getNextToken());
		T();
	}

	if(strcmp(lookAhead, "$\0") == 0)
	{
		printf("Successfully parsed.");
	} 
	else
	{
		printf("String doesnt belong to grammar");
	}
}

void T() {
	S();

}

int main() {
	strcpy(lookAhead, getNextToken());
	S();
}
