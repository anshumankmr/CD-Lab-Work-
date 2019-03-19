#include<stdio.h>
#include<stdlib.h>

int main() {
	FILE *fa, *fb;
	char x;
	fa = fopen("q1in.c", "r");
	if(fa == NULL) {
		printf("Cannot open file \n");
		exit(0);
	}

	fb = fopen("q1out.txt", "w");

	x = getc(fa);

	while(x != EOF) {
		int flag = 0;
		while(x == ' ' || x == '\t') {
			flag = 1;
			x = getc(fa);
		}
		if(flag) {
			putc(' ', fb);
		}
		putc(x, fb);
		x = getc(fa);
	}
	fclose(fa);
	fclose(fb);
}
