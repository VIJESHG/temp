%{
	#include <stdio.h>
	#include<string.h>
	#include "y.tab.h" 
%}

%%

[\t\n ]+                   /* ignore whitespace */ ;

[!|\.|,|\?] {strcpy(yylval.string,yytext); return PUNCTUATION;}

had |
is |
submits |
go        { printf("%s: is a verb\n", yytext); strcpy(yylval.string,yytext); return VERB; }

dog |
time |
girl |
assignment { printf("%s: is a noun\n", yytext); strcpy(yylval.string,yytext); return NOUN; }

I |
This |
her |
Their {printf("%s : is a pronoun\n", yytext); strcpy(yylval.string,yytext); return PRONOUN; }

a |
an |
the |
A |
An |
The {printf("%s : is an article \n", yytext); strcpy(yylval.string,yytext); return ARTICLE;}

on |
in {printf("%s : is an preposition \n", yytext); strcpy(yylval.string,yytext); return PREPOSITION;}

oh |
ah {printf("%s : is an interjection \n", yytext); strcpy(yylval.string,yytext); return INTERJECTION;}

and |
or |
because {printf("%s : is an conjunction \n", yytext); strcpy(yylval.string,yytext); return CONJUNCTION;}

very |
kindly |
slowly |
here |
often {printf("%s : is an adverb \n", yytext); strcpy(yylval.string,yytext); return ADVERB;}

sweet |
loyal |
friendly {printf("%s : is an adjective \n", yytext); strcpy(yylval.string,yytext); return ADJECTIVE;}

"exit"   {exit(0);}
[0-9]+ { printf("Syntax Error: This is not a grammatically correct sentence. \n %s \n", yytext); }

[@|$|#|%|^|&|*|(|)|]+ { printf("Syntax Error: %s \n", yytext); }

[a-zA-Z]+ { printf("%s Cannot recognise part of speech\n", yytext); }

.      { ECHO;  }

%%


yywrap()
{
  return(0);
}

