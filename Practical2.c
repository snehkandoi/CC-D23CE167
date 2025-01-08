#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numStates;
    int numSymbols;
    int initialState;
    int numAcceptingStates;
    int* acceptingStates;
    int** transitionTable;
} FiniteAutomaton;

int isValidString(FiniteAutomaton* fa, char* inputString) {
    int currentState = fa->initialState;

    for (int i = 0; i < strlen(inputString); i++) {
        char currentSymbol = inputString[i];
        int symbolIndex = -1;

        for (int j = 0; j < fa->numSymbols; j++) {
            if (currentSymbol == (char)('a' + j)) {
                symbolIndex = j;
                break;
            }
        }

        if (symbolIndex == -1) {
            return 0;
        }
        currentState = fa->transitionTable[currentState][symbolIndex];
    }
    for (int i = 0; i < fa->numAcceptingStates; i++) {
        if (fa->acceptingStates[i] == currentState) {
            return 1;
        }
    }

    return 0;
}

int main() {
    FiniteAutomaton fa;

    printf("Number of input symbols: ");
    scanf("%d", &fa.numSymbols);

    char inputSymbols[fa.numSymbols];
    printf("Input symbols: ");
    for (int i = 0; i < fa.numSymbols; i++) {
        scanf(" %c", &inputSymbols[i]);
    }

    printf("Enter number of states: ");
    scanf("%d", &fa.numStates);

    printf("Initial state: ");
    scanf("%d", &fa.initialState);

    printf("Number of accepting states: ");
    scanf("%d", &fa.numAcceptingStates);

    fa.acceptingStates = (int*) malloc(fa.numAcceptingStates * sizeof(int));
    printf("Accepting states: ");
    for (int i = 0; i < fa.numAcceptingStates; i++) {
        scanf("%d", &fa.acceptingStates[i]);
    }

    fa.transitionTable = (int**) malloc(fa.numStates * sizeof(int*));
    for (int i = 0; i < fa.numStates; i++) {
        fa.transitionTable[i] = (int*) malloc(fa.numSymbols * sizeof(int));
    }

    printf("Transition table:\n");
    for (int i = 0; i < fa.numStates; i++) {
        for (int j = 0; j < fa.numSymbols; j++) {
            char symbol = inputSymbols[j];
            printf("%d to %c -> ", i, symbol);
            scanf("%d", &fa.transitionTable[i][j]);
        }
    }

    char inputString[100];
    printf("Input string: ");
    scanf("%s", inputString);

    if (isValidString(&fa, inputString)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    free(fa.acceptingStates);
    for (int i = 0; i < fa.numStates; i++) {
        free(fa.transitionTable[i]);
    }
    free(fa.transitionTable);

    return 0;
}
