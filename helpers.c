#include "helpers.h"
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int LENGTH = 1000;

int getInputNumbers(int** numbers) {
    char input[LENGTH];

    printf("%s", INPUT_MSG);
    fflush(stdin);
    fgets(input, LENGTH, stdin);

    // Replace the newline character with null character
    input[strcspn(input, "\n")] = '\0';

    while (!checkAllNumeric(input)) {
        printf("%s%s", INPUT_ERROR_MSG, INPUT_MSG);
        fflush(stdin);
        fgets(input, LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0';
    }

    char* splitBySpaces = strtok(input, " ");
    return convertInputStringToNumbers(numbers, splitBySpaces);
}

int getFrameSize() {
    int frames;

    printf("Enter frame size: ");
    
    while (scanf("%d", &frames) != 1 || frames <= 0) {
        printf("Please enter a positive integer!\n");
        printf("Enter frame size: ");
        fflush(stdin);
    }

    return frames;
}

int convertInputStringToNumbers(int** numbers, char* inputSplitted) {
    int index = 0;

    while (inputSplitted != NULL) {
        *numbers = realloc(*numbers, (index + 1) * sizeof(int));

        if (!*numbers) {
            fprintf(stderr, "%s", MEMORY_ALLOCATION_FAILED);
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
