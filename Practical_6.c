#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char *input;
int pos = 0;  

bool S();
bool L();
bool L_prime();
void validate(const char *str);

bool match(char expected) {
    if (input[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

bool S() {
    if (match('a')) {
        return true;
    } else if (match('(')) {
        if (L() && match(')')) {
            return true;
        }
    }
    return false;
}


bool L() {
    if (S()) {
        return L_prime();
    }
    return false;
}


bool L_prime() {
    if (match(',')) {
        if (S()) {
            return L_prime();
        }
        return false;
    }
    return true;
}


void validate(const char *str) {
    input = str;
    pos = 0;  
    if (S() && input[pos] == '\0') {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
}

int main() {
    char user_input[100];
    printf("Enter a string: ");
    scanf("%99s", user_input);
    validate(user_input);
    return 0;
}