#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    KEYWORD, IDENTIFIER, CONSTANT, STRING, PUNCTUATION, OPERATOR, INVALID
} TokenType;

typedef struct {
    char value[100];
    TokenType type;
} Token;

const char *keywords[] = {
    "int", "char", "void", "return", "struct", "long", "float", "if", "else", "for", "while", "break", "continue"
};
const int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

const char punctuations[] = {'{', '}', '(', ')', ',', ';', ':'};

const char *operators[] = {"+", "-", "=", "*", "/", "%", "++", "--", "&&", "||", "!"};
const int operator_count = sizeof(operators) / sizeof(operators[0]);

char symbol_table[100][100];
int symbol_count = 0;


int is_keyword(const char *word) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(word, keywords[i]) == 0) return 1;
    }
    return 0;
}

int is_punctuation(char ch) {
    for (int i = 0; i < sizeof(punctuations); i++) {
        if (ch == punctuations[i]) return 1;
    }
    return 0;
}

int is_operator(const char *word) {
    for (int i = 0; i < operator_count; i++) {
        if (strcmp(word, operators[i]) == 0) return 1;
    }
    return 0;
}

void add_to_symbol_table(const char *identifier) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], identifier) == 0) return;
    }
    strcpy(symbol_table[symbol_count++], identifier);
}

void tokenize(char *line) {
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
        if (is_keyword(token)) {
            printf("Keyword: %s\n", token);
        } else if (isalpha(token[0]) || token[0] == '_') {
            printf("Identifier: %s\n", token);
            add_to_symbol_table(token);
        } else if (isdigit(token[0])) {
            int valid = 1;
            for (int i = 1; i < strlen(token); i++) {
                if (!isdigit(token[i])) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                printf("Constant: %s\n", token);
            } else {
                printf("Invalid Token: %s\n", token);
            }
        } else if (token[0] == '\'' || token[0] == '\"') {
            printf("String: %s\n", token);
        } else if (is_operator(token)) {
            printf("Operator: %s\n", token);
        } else if (strlen(token) == 1 && is_punctuation(token[0])) {
            printf("Punctuation: %s\n", token);
        } else {
            printf("Invalid Token: %s\n", token);
        }
        token = strtok(NULL, " \t\n");
    }
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Error: Cannot open file.\n");
        return 1;
    }
    char line[1024];
    printf("TOKENS:\n");
    while (fgets(line, sizeof(line), file)) {
        tokenize(line);
    }
    printf("\nSYMBOL TABLE:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%s\n", symbol_table[i]);
    }
    fclose(file);
    return 0;
}
