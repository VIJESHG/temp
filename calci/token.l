%{
%}
 
DIGIT [0-9]+\.?|[0-9]*\.[0-9]+
 
%%
 
{DIGIT}    {yylval=atof(yytext);return NUM;}
[ \t] ;
\n|.    {return yytext[0];}
