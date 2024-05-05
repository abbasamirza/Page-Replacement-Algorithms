#include "helpers.h"
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Maximum length of input numbers
const int LENGTH = 1000;

// --- GET INPUT FUNCTIONS ---
int getInputNumbers(int** numbers) {
    char input[LENGTH];

    printf("%s", INPUT_MSG);
    fflush(stdin);
    fgets(input, LENGTH, stdin);

    // Replace the newline character with null character
    input[strcspn(input, "\n")] = '\0';

    // Prompt user for input until input is not all numeric
    while (!checkAllNumeric(input)) {
        printf("%s%s", INPUT_TYPE_ERROR_MSG, INPUT_MSG);
        fflush(stdin);
        fgets(input, LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0';
    }

    // Get numbers one by one split up by space
    char* splitBySpaces = strtok(input, " ");
    
    return convertInputStringToNumbers(numbers, splitBySpaces);
}

int getFrameSize() {
    int frames;

    printf("Enter frame size: ");
    
    // Prompt user until he doesn't provide a type 'number' or a number greater than zero
    while (scanf("%d", &frames) != 1 || frames <= 0) {
        printf("Please enter a positive integer!\n");
        printf("Enter frame size: ");
        fflush(stdin);
    }

    return frames;
}

void getChoice(int* choice, int lower, int upper) {
    // Check if user has provided input of type 'number' and that input should be in range
    while (scanf("%d", choice) != 1 || (*choice < lower || *choice > upper)) {
        printf("\t\t%s", INPUT_TYPE_ERROR_MSG);
        printf("\t\tOr enter a number in the range of the menu (%d to %d)\n", lower, upper);
        printf("\t\t\b\b\b-> ");
        fflush(stdin);
    }

    // Clear screen after choosing from menu
    system("clear");
}
// --- GET INPUT FUNCTIONS ---

// --- DISPLAY FUNCTIONS ---
void displayAlgorithmsName(char* name) {
    printf("\t----------------------------------------\n");
    printf("\t\t\b\b\b--- %s ---\n", name);
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

void displayFrameState(int numbers[], int frame[], int length, int index) {
    printf("\n");
    printf("\t%d\t\t", numbers[index]);

    for (int j = 0; j < length; j++) {
        if (frame[j] != -1) {
            printf("%d\t", frame[j]);
        } else {
            printf("-\t");
        }
    }
}

void displayOutputResults(int pageHits, int pageFaults) {
    printf("\n\n\tPage Hits: %d\n", pageHits);
    printf("\tPage Faults: %d\n", pageFaults);
    printf("\t----------------------------------------\n");
}
// --- DISPLAY FUNCTIONS ---

// --- HELPER/MANIPULATION FUNCTIONS ---
int convertInputStringToNumbers(int** numbers, char* inputSplitted) {
    int index = 0;

    while (inputSplitted != NULL) {
        // Allocate memory on run time according to numbers entered by the user
        *numbers = realloc(*numbers, (index + 1) * sizeof(int));

        if (!*numbers) {
            fprintf(stderr, "%s", MEMORY_ALLOCATION_FAILED);
            exit(EXIT_FAILURE);
        }

        // Convert to number and store in array
        (*numbers)[index] = atoi(inputSplitted);
        index++;

        // Move to the next number
        inputSplitted = strtok(NULL, " ");
    }

    // Return the total length
    return index;
}

bool checkAllNumeric(char* input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i]) && input[i] != ' ')
            return false;
    }

    return true;
}

void implementSingleAlgorithm(void* algorithm(void*), Input input) {
    // This function will implement the algorithm passed in the parameter
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

void assignDefaultFrameValues(int* frame, int length) {
    printf("\tIncoming\t");

    for (int i = 0; i < length; i++) {
        printf("Frame %d\t", i + 1);
        frame[i] = -1;
    }

    printf("\n");
}

bool checkPageHit(int* numbers, int* frame, int length, int i) {
    for (int j = 0; j < length; j++) {
        // Check if page is already in frame
        if (numbers[i] == frame[j]) {
            return true;
        }
    }

    return false;
}

void OPRSearch(int* numbers, int* frame, int* pos, int* index, int length, int count, int i) {
    for (int j = 0; j < length; j++) {
        bool found = false;

        for (int k = i + 1; k < count; k++) {
            if (frame[j] == numbers[k]) {
                found = true;

                if (*pos < k) {
                    *pos = k;
                    *index = j;
                }

                break;
            }
        }

        if (!found) {
            *pos = count;
            *index = j;
        }
    }
}

void LRUSearch(int* numbers, int* frame, int* distance, int* max, int* index, int length, int i) {
    for (int j = 0; j < length; j++) {
        distance[j] = 0;

        for (int k = i - 1; k >= 0; k--) {
            ++distance[j];

            if (frame[j] == numbers[k]) {
                break;
            }
        }

        if (distance[j] > *max) {
            *max = distance[j];
            *index = j;
        }
    }
}
// --- HELPER/MANIPULATION FUNCTIONS ---
