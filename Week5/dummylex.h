#ifndef DUMMY_LEX__H
#define DUMMY_LEX__H
char tokens[20][20] = {
	"num",
	"*",
	"num",
	"*",
	"num",
	"EOL"
};

int curr = -1;
char lookAhead[20];

char* getNextToken() {
	return tokens[++curr];
}
#endif