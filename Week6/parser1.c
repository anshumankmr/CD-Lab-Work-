#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "clexAnalyser.h"
struct token* t = NULL;
void looping_stat();
void assign_stat();
void expn();
void statement_list();
void simple_expn();
void eprime();
void seprime();
void factor();
void term();
void mulop();
void addop();
void statement();
void declarations();
void data_type();
void identifier_list();
void tprime();
int isDataType();
void relop();
void labeled_stat();
int ct = 0;
void ERROR() {
	printf("Error no. : %d\n", ct);
	printf("Not accepted by grammar for 'for' loop. Line: %d, Col: %d %d %s\n", t->rowno, t->colno, t->type, t->lexeme);
	exit(1);
}
void looping_stat() {
	if(!strcmp(t->lexeme, "for")) {
		t = getNextToken();
		if(!strcmp(t->lexeme, "(")) {
			t = getNextToken();
			assign_stat();
			if(!strcmp(t->lexeme, ";")) {
				t = getNextToken();
				expn();
				if(!strcmp(t->lexeme, ";")) {
					t = getNextToken();
					assign_stat();
					if(!strcmp(t->lexeme, ")")) {
						t = getNextToken();
						if(!strcmp(t->lexeme, "{")) {
							t = getNextToken();
							statement_list();
							if(!strcmp(t->lexeme, "}")) {
								t = getNextToken();
							} else {
								ct++;
								ERROR();
							}
						} else {
							ct++;
							ERROR();
						}
					} else {
						ct++;
						ERROR();
					}
				} else {
					ct++;
					ERROR();
				}
			} else {
				ct++;
				ERROR();	
			}
		} else {
			ct++;
			ERROR();
		}
	} else {
		ct++;
		ERROR();
	}
}

void assign_stat() {
	if(t->type == ID) {
		t = getNextToken();
		if(t->type == ASSIGN_OP) {
			if(!strcmp(t->lexeme, "++") || !strcmp(t->lexeme, "--")) {
				t = getNextToken();
			} else {
				t = getNextToken();
				expn();	
			}
		} else {
			ct++;
			ERROR();
		}
	} else {
		ERROR();
	}
}

void expn() {
	simple_expn();
	eprime();
}

void simple_expn() {
	term();
	seprime();

}

void term() {
	factor();
	tprime();
}

void factor() {
	if(t->type == ID || t->type == NUM_CONST) {
		t = getNextToken();
	} else {
		ERROR();
	}
}

void tprime() {
	if(!strcmp(t->lexeme,"*") || !strcmp(t->lexeme,"/")) {
		mulop();
		factor();
		tprime();
	}
}

void mulop() {
	if(!strcmp(t->lexeme,"*") || !strcmp(t->lexeme,"/")) {
		t = getNextToken();
	} else {
		ERROR();
	}
}

void seprime() {
	if(!strcmp(t->lexeme,"+") || !strcmp(t->lexeme,"-")) {
		addop();
		term();
		seprime();
	}	
}

void addop() {
	if(!strcmp(t->lexeme,"+") || !strcmp(t->lexeme,"-")) {
		t = getNextToken();
	} else {
		ERROR();
	}

}

void eprime() {
	if(t->type == REL_OP) {
		relop();
		simple_expn();
	}
}

void relop() {
	if(t->type == REL_OP) {
		t = getNextToken();
	} else {
		ERROR();
	}
}

void statement_list() {
	if(!t)
		return;
	if(t->type == ID || !strcmp(t->lexeme,"if") || !strcmp(t->lexeme,"for") || isDataType(t->lexeme) || !strcmp(t->lexeme,"switch")) {
		statement();
		statement_list();
	}
}

int isDataType(char * s) {
	return !strcmp(t->lexeme,"int") || !strcmp(t->lexeme,"float") || !strcmp(t->lexeme,"short") || !strcmp(t->lexeme,"long") || !strcmp(t->lexeme,"double");
}


void statement() {
	if(t->type == ID) {
		assign_stat();
		if(!strcmp(t->lexeme,";")) {
			t = getNextToken();
			return;
		} else {
			ERROR();
		}
	} else if(!strcmp(t->lexeme,"for")) {
		looping_stat();
	} else if(isDataType(t->lexeme)) {
		declarations();
	} else if(!strcmp(t->lexeme,"switch")) {
		// TODO: Consider all decision statements
		t = getNextToken();
		if(!strcmp(t->lexeme, "(")) {
			t = getNextToken();
			expn();
			if(!strcmp(t->lexeme,")")) {
				t = getNextToken();
				if(!strcmp(t->lexeme,"{")) {
					t = getNextToken();
					labeled_stat();
					if(!strcmp(t->lexeme,"}")) {
						t = getNextToken();
					} else {
						ERROR();
					}
				} else {
					ERROR();	
				}
			} else {
				ERROR();
			}
		} else {
			ERROR();
		}
	}else {
		ERROR();
	}
}

void labeled_stat() {
	if(!strcmp(t->lexeme,"case")) {
		t = getNextToken();
		if(t->type == NUM_CONST || t->type == CHAR_LITERAL) {
			t = getNextToken();
			if(!strcmp(t->lexeme,":")) {
				t = getNextToken();
				statement_list();
			} else {
				ERROR();
			}
		} else {
			ERROR();
		}
	}
}
void declarations() {
	if(isDataType(t->lexeme)) {
		data_type();
		identifier_list();
		if(!strcmp(t->lexeme,";")) {
			t = getNextToken();
		} else {
			ERROR();
		}
		declarations();
	}
}

void data_type() {
	if(isDataType(t->lexeme)){
		t = getNextToken();
	} else {
		ERROR();
	}
}

void identifier_list() {
	if(t->type == ID) {
		t = getNextToken();
		if(!strcmp(t->lexeme,",")) {
			t = getNextToken();
			identifier_list();
		} else if (!strcmp(t->lexeme,"[")) {
			t = getNextToken();
			if(t->type==NUM_CONST) {
				t =getNextToken();
				if(!strcmp(t->lexeme,"]")) {
					t = getNextToken();
					if(!strcmp(t->lexeme,",")) {
						t = getNextToken();
						identifier_list();
					}
				}
			} else {
				ERROR();
			}
		}
	} else {
		ERROR();
	}
}

int main() {
	fp = fopen("input.c", "r");
	t = getNextToken();
	statement_list();
	if(!getNextToken()) {
		printf("The given string is accepted.\n");
	}
	int x = 0;
	switch(x) {
		x:
			printf("sda\n");
	}
}
