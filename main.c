#include "helpers.h"
#include "algorithms.h"
#include "messages.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

void assignDefaultValues(Input*);

int main(int argc, char* argv[]) {
    Input input;
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
                fprintf(stderr, "%s", MEMORY_ALLOCATION_FAILED);
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < input.count; i++) {
                input.numbers[i] = atoi(argv[i + 1]);
            }
        } else {
            printf("%s", INPUT_ERROR_MSG);
            input.count = getInputNumbers(&input.numbers);
        }
    } else {
        printf("You can also use command-line for giving input!\n");
        input.count = getInputNumbers(&input.numbers);
    }

    input.frames = getFrameSize();

    pthread_t FIFOThread;

    if (pthread_create(&FIFOThread, NULL, FIFO, (void*)&input) != 0) {
        fprintf(stderr, "%s", THREAD_CREATION_FAILED);
        exit(EXIT_FAILURE);
    }

    if (pthread_join(FIFOThread, NULL) != 0) {
        fprintf(stderr, "%s", THREAD_JOINING_FAILED);
        exit(EXIT_FAILURE);
    }

    free(input.numbers);

    return 0;
}

void assignDefaultValues(Input* input) {
    input->numbers = NULL;
    input->count = 0;
    input->frames = 0;
}
