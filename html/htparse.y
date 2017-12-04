%{
    #include<ctype.h>
    #include<stdio.h>
%}
 
%token HEAD TEXT CLOSEHEAD
 
%%
S :  a b c '\n' {printf("Correct input");}
	| {printf("error");} 
	;
a : HEAD
   ;
b : TEXT
  ;
c : CLOSEHEAD
  ;
%%
#include"lex.yy.c" 
int main(){
    printf("Exp: ");
    yyparse();
}
