#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* KEYWORDS[] = {"int", "char", "float", "double", "void"};
FILE *fa;
void find(char word[], int l, int c) {
	for(int i=0; i < 5; i++) {
		if(strcmp(KEYWORDS[i], word) == 0) {
			printf("%s at %d,%d\n", word, l, c);
		}
	}
}
int main() {
	
	char x;
	fa = fopen("q3in.c", "r");
	if(fa == NULL) {
		printf("Cannot open file \n");
		exit(0);
	}

	x = getc(fa);
	char* key = "int";
	char* word = (char*) malloc(sizeof(char)*100);
	int i=0;
	int line_no = 0;
	int col_no = 0;
	int col;
	while(x != EOF) {
		if(x == '"') {
			x = getc(fa);
			col_no++;
			while(x != '"') {
				x = getc(fa);
				col_no++;
			}
		}
		int flag = 0;
		while(x != ' ' && x != '\n') {
			if(!flag) {
				col = col_no;	
				flag = 1;
			}			
			if(x == EOF)
				break;
			word[i++] = x;
			x = getc(fa);
			col_no++;
		}

		word[i] = '\0';
		i=0;
		find(word, line_no, col);
		if(x == '\n'){
			line_no++;
			col_no=0;
		}
		x = getc(fa);
	}
	fclose(fa);
}