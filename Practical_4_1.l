%{
#include <stdio.h>
%}

%%
[0-9]+          { printf("%s\n", yytext); }
[ \t\n]         ; /* Ignore whitespace */
.              ; /* Ignore other characters */
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
