%{
	int posInt = 0;
	int negInt = 0;
	int posFloat = 0;
	int negFloat = 0;
%}

%%
\-[0-9]+ { negInt++; }
\+?[0-9]+ { posInt++; }
\-[0-9]+\.[0-9]+ { negFloat++; }
\+?[0-9]+\.[0-9]+ { posFloat++; }
%%

int main(int argc, char** argv) {
	yylex();

	printf("Positive Integers: %d\tNegative Integers: %d\tPos Float: %d\nNeg Float: %d", posInt, negInt, posFloat, negFloat);
}
int yywrap() {
	return 1;
}