%{
	int simple = 1;
%}

%%
[a-zA-Z]+[ ]and[ ][a-zA-Z]+ { simple = 0; }
%%

int main(int argc, char** argv) {
	yylex();
	printf("The sentence is %d",simple);
}

int yywrap() {
	return 1;
}