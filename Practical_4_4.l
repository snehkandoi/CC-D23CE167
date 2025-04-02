%{
#include <stdio.h>
#include <ctype.h>

int lower = 0, upper = 0, digit = 0, special = 0, length = 0;
%}

%%

[a-z]      { lower = 1; length++; }
[A-Z]      { upper = 1; length++; }
[0-9]      { digit = 1; length++; }
[*;#$@]    { special = 1; length++; }
.|\n       { length++; }

%%

int main() {
    yylex();
    if (length >= 9 && length <= 15 && lower && upper && digit && special) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}