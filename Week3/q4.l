%{
	int scans = 0;
	int prints = 0;
%}

%%
scanf {scans++; fprintf(yyout, "READ"); }
printf {prints++; fprintf(yyout, "PRINT"); }
%%

int main(int argc, char** argv) {
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	yylex();
	printf("scans: %d\nprints: %d", scans, prints);
}
int yywrap() {
	return 1;
}
