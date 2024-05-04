#include "helpers.h"
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

const int LENGTH = 1000;

int getInputNumbers(int** numbers) {
    char input[LENGTH];

    printf("%s", INPUT_MSG);
    fflush(stdin);
    fgets(input, LENGTH, stdin);

    // Replace the newline character with null character
    input[strcspn(input, "\n")] = '\0';

    while (!checkAllNumeric(input)) {
        printf("%s%s", INPUT_TYPE_ERROR_MSG, INPUT_MSG);
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

void getChoice(int* choice, int lower, int upper) {
    while (scanf("%d", choice) != 1 || (*choice < lower || *choice > upper)) {
        printf("\t\t%s", INPUT_TYPE_ERROR_MSG);
        printf("\t\tOr enter a number in the range of the menu (%d to %d)\n", lower, upper);
        printf("\t\t\b\b\b-> ");
        fflush(stdin);
    }

    system("clear");    
}

void displayAlgorithmsName(char* name) {
    printf("\t\t\b\b\b--- %s ---\n\n", name);
}

void implementSingleAlgorithm(void* algorithm(void*), Input input) {
    pthread_t thread;

    if (pthread_create(&thread, NULL, algorithm, (void*)&input) != 0) {
        fprintf(stderr, "%s", THREAD_CREATION_FAILED);
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "%s", THREAD_JOINING_FAILED);
        exit(EXIT_FAILURE);
    }
}

void displayContinueMenu() {
    printf("\n\n\t\t1. Continue (Head to the menu)\n");
    printf("\t\t2. Exit\n\n");
    printf("\t\tEnter the number of the action you want to perform\n");
    printf("\t\t\b\b\b-> ");
}

void displayTypingEffect(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        printf("%c", str[i]);
        fflush(stdout);
        usleep(50000);
    }
}
