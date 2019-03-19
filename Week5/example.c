#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dummylex.h"

void T(void);
void E() {
	if(strcmp(lookAhead, "num\0") == 0) {
		strcpy(lookAhead, getNextToken());
		T();
	} 

	if(strcmp(lookAhead, "EOL\0") == 0) {
		printf("Successfully parsed.\n");
	} else {
		printf("String does not belong to the grammar.\n");
		exit(1);
	}
}

void T() {
	if(strcmp(lookAhead, "*\0") == 0) {
		strcpy(lookAhead, getNextToken());
		if(strcmp(lookAhead, "num\0") == 0) {
			strcpy(lookAhead, getNextToken());
			T();
		} else {
			printf("String does not belong to the grammar\n");
			exit(1);
		}
	} else {
		return;
	}
}

int main() {
	strcpy(lookAhead, getNextToken());
	E();
}