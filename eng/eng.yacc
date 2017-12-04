%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>      
	#include "y.tab.h"
%}

%union {
	char string[10];
}


%token <string> NOUN
%token <string> VERB
%token <string> ARTICLE
%token <string> ADVERB
%token <string> ADJECTIVE
%token <string> INTERJECTION
%token <string> CONJUNCTION
%token <string> PREPOSITION
%token <string> PUNCTUATION
%token <string> PRONOUN

%%
sent: sent sent
| ARTICLE NOUN VERB PREPOSITION ARTICLE ADVERB ADJECTIVE NOUN PUNCTUATION {printf("grammatically correct\n"); }
| sent CONJUNCTION sent {printf("grammatically correct\n");}
| NOUN VERB ARTICLE NOUN PUNCTUATION {printf("grammatically correct\n");}
| PRONOUN VERB ARTICLE NOUN PUNCTUATION {printf("grammatically correct\n");}
| PRONOUN VERB ARTICLE ADJECTIVE NOUN PUNCTUATION {printf("grammatically correct\n");}
| NOUN VERB PRONOUN NOUN PREPOSITION NOUN PUNCTUATION {printf("grammatically correct\n");};
%%
extern FILE *yyin;
#include"lex.yy.c"
int main() {
	yyparse();
	return 0;
}


yyerror() {
	printf("\nERROR!!\n");
}

