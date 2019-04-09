#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct token
{
  char * lexeme;
  char type[10];
  int index;
  char retType[10];
  int row,col;
  int numArgs;
  int scope;
  int size;
};
struct token* allocToken() {
	struct token* tk;
	tk = (struct token*) malloc(sizeof(struct token));
	tk->lexeme = (char*) malloc(sizeof(char)*1000);
	tk->index = -1;
	// tk->type = EOFILE;
	return tk;
}

void setTokenArgs(struct token* tk, char* lexeme, int index, int rowno, int colno, char* type,int scope, char* retType, int numArgs) {
	if(!tk)
		return;
	strcpy(tk->lexeme, lexeme);
	strcpy(tk->type, type);
	strcpy(tk->retType, retType);
	tk->index = index;
	tk->row = rowno;
	tk->col = colno;
	tk->numArgs = numArgs;
	tk->scope = scope;

}// end of token function
struct node
{
  struct node* next;
  struct token object;
};
struct node* hashTable[100];
struct node* newnode(struct token obj)
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->object = obj;
  temp->next = NULL;
  return temp;
}
void init()
{
  for (int i = 0 ; i < 100; i++)
  {
    hashTable[i]=NULL;
  }
}
void printlist(struct node* head )
{
  while(head)
  {
    printf("%s %s",(head->object).lexeme,(head->object).type);
    head = head->next;
  }
}
int  hashFunction(char str[])
{
 int i,sum=0;
 for(i =0;str[i]!='\0';i++)
 {
  sum+=(int)str[i];
 }
 return sum/strlen(str);
}
int searchList(char str[])
{
  int hash = hashFunction(str);
  struct node* temp = hashTable[hash];
  while (temp)
  {
    if (strcmp((temp->object).lexeme,str)==0)
    {
      return 1;
    }
    temp= temp->next;
  }
  return 0;
}
void insertList(struct node* head, struct token obj)
{
  struct node* temp = newnode(obj);
  while (head)
  {
    head=head->next;
  }
  head->next=temp;
}
void display(struct node* head)
{
  while(head)
  {
    printf(" Lexeme %s Type %s Index %d RetType %s Row %d Col %d NumArgs %d Scope %d Size %d\n",head->lexeme,head->type,head->index,head->retType,head->row,head->col,head->numArgs,head);
    head= head->next;
  }
}
void insert(struct token obj)
{
  if (search(obj)==0)
  {
   insertList(hashTable[hashFunction(obj->lexeme)],obj);
  }
  else
  {
    printf("It is Already There\n", );
  }
}
