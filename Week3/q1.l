%{
	int vowels = 0;
	int consonants = 0;
%}

%%
[aeiou] { vowels++; }
[a-z] { consonants++; }
%%

int main(int argc, char** argv) {
	yylex();
	printf("vowels: %8d | consonants: %8d", vowels, consonants);
} 
int yywrap() {
	return 1;
}