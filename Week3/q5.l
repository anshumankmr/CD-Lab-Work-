%{
	int simple = 1;
%}

%%
[a-zA-Z]+[ ]and[ ][a-zA-Z]+ { simple = 0; }
%%

int main(int argc, char** argv) {
	yylex();
	char* ans = simple == 1 ? "simple" : "compound";
	printf("The sentence is %s", ans);
}

int yywrap() {
	return 1;
}