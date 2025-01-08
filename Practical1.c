#include <stdio.h>
#include <string.h>

int validateString(char* str) {
    int len = strlen(str);

    if (len < 2) {
        return 0;
    }

    if (str[len - 1] != 'b' || str[len - 2] != 'b') {
        return 0;
    }

    for (int i = 0; i < len - 2; i++) {
        if (str[i] != 'a') {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    if (validateString(str)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
