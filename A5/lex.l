%{
	#include<stdio.h>
	#include "y.tab.h"
	extern char yyval;
	
%}

NUMBER [0-9]+
LETTER [a-zA-Z]+

%%

{NUMBER} {yylval.sym = (char)yytext[0]; return NUMBER;}
{LETTER} {yylval.sym = (char)yytext[0];return LETTER;}


. {return yytext[0];}

%%

int yywrap()
{
	return 1;
}
