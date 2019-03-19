#include<stdio.h>
#include<stdlib.h>

int main() {
	FILE *fa, *fb;
	char x,y;
	fa = fopen("q2in.c", "r");
	if(fa == NULL) {
		printf("Cannot open file \n");
		exit(0);
	}

	fb = fopen("q2out.c", "w");

	x = getc(fa);
	int flag = 0;
	while(x != EOF) {
		if(x != '#') {
			while(x != '\n'){
				putc(x,fb);
				x = getc(fa);
			}
			putc(x,fb);
			x = getc(fa);
		} else {
			while(x != '\n')
				x = getc(fa);
		}
	}
}
