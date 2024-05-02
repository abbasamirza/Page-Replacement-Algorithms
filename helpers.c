#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int LENGTH = 1000;
const char* INPUT_MSG = "Enter the reference string/page numbers (numbers should be space separated!): ";

int getInputNumbers(int** numbers) {
    char input[LENGTH];

    printf("%s", INPUT_MSG);
    fgets(input, LENGTH, stdin);

    // Replace the newline character with null character
    input[strcspn(input, "\n")] = '\0';

    while (!checkAllNumeric(input)) {
        printf("Invalid input! Please enter numbers only\n%s", INPUT_MSG);
        fgets(input, LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0';
    }

    char* splitBySpaces = strtok(input, " ");
    return convertInputStringToNumbers(numbers, splitBySpaces);
}

int convertInputStringToNumbers(int** numbers, char* inputSplitted) {
    int index = 0;

    while (inputSplitted != NULL) {
        *numbers = realloc(*numbers, (index + 1) * sizeof(int));

        if (!*numbers) {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        (*numbers)[index] = atoi(inputSplitted);
        index++;

        // Move to the next number
        inputSplitted = strtok(NULL, " ");
    }

    return index;
}

bool checkAllNumeric(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i]) && input[i] != ' ')
            return false;
    }

    return true;
}
