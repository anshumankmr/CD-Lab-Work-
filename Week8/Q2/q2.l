%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "q2.tab.h"
%}
alpha [a-zA-Z]
digit [0-9]
%%
";" {printf("%s\n",yytext); return SS;}
"for" {printf("%s\n",yytext); return FOR;}
"int" {printf("%s\n",yytext); return INT;}
"char" {printf("%s\n",yytext); return CHAR;}
"float" {printf("%s\n",yytext); return FLOAT;}
[ \t]	{printf("%s\n",yytext); return TAB;};
[ \n]   {printf("%s\n",yytext); return NL;}
"main"  {printf("%s\n",yytext); return MAIN;}
"case"	{printf("%s\n",yytext);return CASE;}
"break"	{printf("%s\n",yytext);return BREAK;}
"void" {printf("%s\n",yytext);return VOID;}
"while"	{printf("%s\n",yytext);return WHILE;}
"switch"	{printf("%s\n",yytext);return SWITCH;}
"default" {printf("%s\n",yytext);return DEFAULT;}
"if"	{printf("%s\n",yytext);return IF;}
"else"	{printf("%s\n",yytext);return ELSE;}
{digit}+ {printf("%s\n",yytext);return NUM;}
{alpha}({alpha}|{digit})* {printf("%s\n",yytext);return ID;}
"="    { printf("%s\n",yytext);return ASGN;}
"<="    {printf("%s\n",yytext);return LE;}
">="    {printf("%s\n",yytext);return GE;}
"=="    {printf("%s\n",yytext);return EQ;}
"!="    {printf("%s\n",yytext);return NE;}
">"	{printf("%s\n",yytext);return GT;}
"<"	{printf("%s\n",yytext);return LT;}
"+" 	{printf("%s\n",yytext);return PLUS;}
"-"  	{printf("%s\n",yytext);return MINUS;}
"*" 	{printf("%s\n",yytext);return MULOP;}
"/"	{printf("%s\n",yytext);return DIV;}
"(" {printf("%s\n",yytext);return OB;}
")" {printf("%s\n",yytext);return CB;}
"{" {printf("%s\n",yytext);return OCB;}
"}" {printf("%s\n",yytext);return CCB;}
"[" {printf("%s\n",yytext);return OSB;}
"]" {printf("%s\n",yytext);return CSB;}
"," {printf("%s\n",yytext);return CO;}
"%" {printf("%s\n",yytext);return MOD;}
\/\/.* ;
\/\*(.*\n)*.*\*\/ ;
.       return yytext[0];
%%%%
int yywrap()
{
	return 1;
}