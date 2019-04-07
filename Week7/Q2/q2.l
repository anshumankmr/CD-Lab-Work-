%{
	#include "q2.tab.h"
	int ifcount=0;
	int elsecount=0;
%}

%%
"if" { ifcount++; return I; }
"else" {elsecount++;return EL;}
\n {return NL;}
"(" {return OB;}
")" {return CB;}
"{" {return OCB;}
"}" {return CCB;}
"=" {return EQ;}
"==" {return EE;}
"!=" {return NE;}
"<=" {return LTE;}
">=" {return GTE;}
">" {return GT;}
"<" {return LT;}
";" {return SC;}
[0-9]+ {return NUM;}
[a-zA-Z][a-zA-Z0-9_]* {return ID;}
%%

int yywrap() {
	printf("If count : %d\n", ifcount);
	printf("Else count : %d\n", elsecount);
	return 1;
}
