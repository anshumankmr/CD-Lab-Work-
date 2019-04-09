#include <string.h>
#include <stdio.h>
char *tokens[10000];
char lookAhead[80];
char input[100000];
int curr = -1;
void init()
{
	// printf("jij");
	// FILE * fp  = fopen("input.txt","r");
    gets(input);
    int i =0;
    // printf("%s\n",input );
    // tokens = strtok(input," ");
    // printf("sdfdsf\n");
     char *p = strtok(input," ");
    // char *array[1000];
    while (p != NULL)
    {
        tokens[i++] = p;
        p = strtok (NULL, " ");
    }
    fflush(stdout);
    // for (int j  = 0; j <i ; j++) 
    // {
    // 	puts(tokens[j]);
    // }
    // printf("out of this \n/");
}
char* getNextToken() 
{
    printf("%d\n",curr+1 );
	return tokens[++curr];
}
