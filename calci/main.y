%{
    #include<ctype.h>
    #include<stdio.h>
	#include <math.h>
 	#define YYSTYPE double
 	int yylex();
void yyerror(const char *s);
%}
 
%token NUM

%left '+' '-'
%left '*' '/'
%right UMINUS
 
%%
 
S         : S E '\n' { printf("= %g \nExp :\n", $2); }
           | S '\n'
           |
           | error '\n' { yyerror("Syntax error...\n" );yyerrok; }
           ;
E         : E '+' E    { $$ = $1 + $3; }
           | E'-'E    { $$=$1-$3; }
           | E'*'E    { $$=$1*$3; }
            
            |E'/'E    { $$=$1/$3; }
           | '('E')'    { $$=$2; }
           | '-'E %prec UMINUS { $$= -$2; }
           | NUM
             
           ;
 
%%
 
#include"lex.yy.c" 
int main()
{
    printf("Exp: ");
    yyparse();
}
