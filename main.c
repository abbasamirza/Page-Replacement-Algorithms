#include "helpers.h"
#include "algorithms.h"
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

// Define menu options for better readability
#define FIFO_ALGORITHM 1
#define OPTIMAL_PAGE_REPLACEMENT 2
#define LEAST_RECENTLY_USED 3
#define SECOND_CHANCE_ALGORITHM 4
#define ALL_ALGORITHMS 5
#define CHANGE_NUMBERS 6
#define CHANGE_FRAME_SIZE 7
#define EXIT 8

void assignDefaultValues(Input*);
void implementAllAlgorithms(Input);

int main(int argc, char* argv[]) {
    Input input;
    int choice;
    assignDefaultValues(&input);

    if (argc > 1) {
        input.count = argc - 1;
        bool allNumeric = true;

        for (int i = 1; i < argc; i++) {
            if (!checkAllNumeric(argv[i])) {
                allNumeric = false;
                break;
            }
        }

        if (allNumeric) {
            input.numbers = (int*)calloc(argc - 1, sizeof(int));

            if (!input.numbers) {
                displayTextInColor(MEMORY_ALLOCATION_FAILED, RED);
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < input.count; i++) {
                input.numbers[i] = atoi(argv[i + 1]);
            }
        } else {
            displayTextInColor(INPUT_TYPE_ERROR_MSG, RED);
            input.count = getInputNumbers(&input.numbers);
        }
    } else {
        displayTextInColor("You can also use command-line for giving input!\n", CYAN);
        input.count = getInputNumbers(&input.numbers);
    }

    input.frames = getFrameSize();
    
    do {
        bool wantsToContinue = false, changesUpdated = false;

        displayMenu();
        fflush(stdin);
        getChoice(&choice, 1, 8);

        if (choice == FIFO_ALGORITHM) {
            displayAlgorithmsName("FIRST IN FIRST OUT (FIFO)");
            implementSingleAlgorithm(FIFO, input);
            wantsToContinue = true;
        } else if (choice == OPTIMAL_PAGE_REPLACEMENT) {
            displayAlgorithmsName("OPTIMAL PAGE REPLACEMENT (OPR)");
            implementSingleAlgorithm(OPR, input);
            wantsToContinue = true;
        } else if (choice == LEAST_RECENTLY_USED) {
            displayAlgorithmsName("LEAST RECENTLY USED (LRU)");
            implementSingleAlgorithm(LRU, input);
            wantsToContinue = true;
        } else if (choice == SECOND_CHANCE_ALGORITHM) {
            displayAlgorithmsName("SECOND CHANCE ALGORITHM (SCA)");
            implementSingleAlgorithm(SCA, input);
            wantsToContinue = true;
        } else if (choice == ALL_ALGORITHMS) {
            implementAllAlgorithms(input);
            wantsToContinue = true;
        } else if (choice == CHANGE_NUMBERS) {
            input.count = getInputNumbers(&input.numbers);
            changesUpdated = true;
        } else if (choice == CHANGE_FRAME_SIZE) {
            input.frames = getFrameSize();
            changesUpdated = true;
        }

        if (wantsToContinue) {
            displayContinueMenu();
            getChoice(&choice, 1, 2);

            if (choice == 2) {
                break;
            }
        }

        if (changesUpdated) {
            displayTypingEffect("Your changes were successfully saved!", GREEN);
            sleep(1);
        }
    } while (choice != EXIT);

    // Delete dynamically allocated memory
    free(input.numbers);

    return 0;
}

void assignDefaultValues(Input* input) {
    input->numbers = NULL;
    input->count = 0;
    input->frames = 0;
}

void implementAllAlgorithms(Input input) {
    displayAlgorithmsName("FIRST IN FIRST OUT (FIFO)");
    implementSingleAlgorithm(FIFO, input);
    printf("\n\n");

    displayAlgorithmsName("OPTIMAL PAGE REPLACEMENT (OPR)");
    implementSingleAlgorithm(OPR, input);
    printf("\n\n");

    displayAlgorithmsName("LEAST RECENTLY USED (LRU)");
    implementSingleAlgorithm(LRU, input);
    printf("\n\n");

    displayAlgorithmsName("SECOND CHANCE ALGORITHM (SCA)");
    implementSingleAlgorithm(SCA, input);
    printf("\n\n");
}
