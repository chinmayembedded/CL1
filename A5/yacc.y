%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	
	int ind=0;
	char temp='A';
	void quadraple();
	char AddToTable(char, char,char);
	struct incod
	{
		char opd1;
		char opd2;
		char opr;
	}; 
%}

%union
{
	char sym;
}

%token <sym> NUMBER LETTER
%type <sym> expr
%left '+' '-'
%right '/' '*'

%%

statement: LETTER '=' expr ';' {AddToTable((char)$1, (char)$3, '=');}
	| expr ';'
;

expr: expr '+' expr {$$ = AddToTable((char)$1, (char)$3,'+');}
    | expr '-' expr {$$ = AddToTable((char)$1, (char)$3,'-');}
    | expr '/' expr {$$ = AddToTable((char)$1, (char)$3,'/');}
    | expr '*' expr {$$ = AddToTable((char)$1, (char)$3,'*');}
    | '('expr')' {$$ = (char)$2;}
    | NUMBER {$$ = (char)$1;}
    | LETTER {$$ = (char)$1;}
;
	
%%
yyerror(char *s)
{
	printf("%s",s);
	exit(0);
}

struct incod code[20];

char AddToTable(char opd1, char opd2, char opr)
{
	code[ind].opd1 = opd1;
	code[ind].opd2 = opd2;
	code[ind].opr = opr;
	ind++;
	temp++;
	return temp;	
}

void quadraple()
{
	int id=0;
	int cnt=0;
	
	printf("\nQuadraple Code\n");
	while(cnt<ind)
	{
		printf("%d",cnt);
		printf("\t");
		printf("%c", code[cnt].opr);
		printf("\t");
		if(isalpha(code[cnt].opd1))
			printf("%c\t",code[cnt].opd1);
		else
			printf("%c\t",temp);
		if(isalpha(code[cnt].opd2))
			printf("%c\t",code[cnt].opd2);
		else
			printf("%c\t",temp);
		printf("%c",temp);
		printf("\n");
		cnt++;
		temp++;
		id++;
	}
}

extern FILE *yyin;

int main()
{
	FILE *myfile= fopen("myfile.txt","r"); 
	if(!myfile)
	{
		printf("ERROR");
		exit(-1);
	}
	yyin = myfile;
	do
	{	
		yyparse();
		temp = 'A';
		quadraple();
		printf("\n");
	}while(!feof(yyin));
}
