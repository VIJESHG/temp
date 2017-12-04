%{
#include <stdio.h>
#include <stdlib.h>
int cno = 0, wno = 0, lno = 0; /*counts of characters, words and lines */
%}

character [a-zA-Z]
digit [0-9]
word ({character}|{digit})+
line \n

%%

{line} { cno++; lno++; }
{word} { wno++; cno += strlen(yytext); }
. { cno++; }

%%

int main(void)
{
    yylex();
    printf("Number of characters: %d; ", cno);
    printf("Number of words:      %d; ", wno);
    printf("Number of lines:      %d\n", lno);
    return 0;
}
