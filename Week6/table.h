#ifndef TABLE_H
#define TABLE_H
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define TABLE_LENGTH 20

struct listElement {
	struct token tok;
	struct listElement* next;
};

struct listElement* symbolTable[TABLE_LENGTH];

struct listElement* newElement(struct token tok) {
	struct listElement* l = (struct listElement*) malloc(sizeof(struct listElement));
	l->tok = tok;
	l->next = NULL;
}

void printList(struct listElement* head) {
	while(head) {
		// printf("%s\t%s\t%d\t%d\t%s\n", (head->tok).lexeme, (head->tok).type, (head->tok).scope, (head->tok).numArgs, (head->tok).retType);
		head = head->next;
	}
}

int searchList(struct listElement* head, char* str) {
	while(head) {
		if(strcmp((head->tok).lexeme, str) == 0)
			return 1;
		head = head->next;
	}
	return 0;
}

void insertList(struct listElement* head, struct token tok) {
	struct listElement* l = newElement(tok);
	while(head->next)
		head = head->next;
	head->next = l;
}

int hashFxn(char* str) {
	int retVal= 0;
	for(int i=0;i<strlen(str);i++)
		retVal+= (int) str[i];
	return retVal%strlen(str);
}
void init() {
	for(int i=0;i<TABLE_LENGTH;i++)
		symbolTable[i] = NULL;
}

void display() {
	printf("NAME\tTYPE\tSCOPE\tNUMARGS\tRETTYPE\n");
	for(int i=0;i<TABLE_LENGTH;i++) {
		printList(symbolTable[i]);
	}
}

int search(char* str) {
	int hashVal = hashFxn(str);
	struct listElement* head = symbolTable[hashVal];
	if(head) {
		return searchList(head, str);
	}
	return 0;
}

void insert(struct token tok) {
	if(search(tok.lexeme))
		return;
	int hashVal = hashFxn(tok.lexeme);
	if(symbolTable[hashVal]) {
		insertList(symbolTable[hashVal], tok);
	} else {
		symbolTable[hashVal] = newElement(tok);
	}
}

#endif