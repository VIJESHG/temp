%{
 #include"y.tab.h"
 #include<string.h>
%}

%% 
\<head\> {return HEAD;}
\<\/head\> {return CLOSEHEAD;}
[a-zA-Z]+  {return TEXT;}
[ \t] ;
\n|.    {return yytext[0];}
