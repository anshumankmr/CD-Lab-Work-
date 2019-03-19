%{
	int words = 0;
	int chars = 0;
	int blanks = 0;
	int lines = 0;
%}

%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
[ ] { blanks++; }
\n { lines++; }
%%

int main(int argc, char** argv) {
	yylex();
	printf("words: %d\tchars: %d\tblanks: %d\tlines: %d", words, chars, blanks, lines);
}
int yywrap() {
	return 1;
}