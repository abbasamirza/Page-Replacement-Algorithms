#include "algorithms.h"
#include "helpers.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* FIFO(void* arg) {
    Input* input = (Input*)arg;
    int* frameStates = malloc(input->frames * sizeof(int));
    int pageFaults = 0, pageHits = 0;

    printf("Incoming\t");

    for (int i = 0; i < input->frames; i++) {
        printf("Frame %d\t", i + 1);
        frameStates[i] = -1;
    }
    printf("\n");

    for (int i = 0; i < input->count; i++) {
        int s = 0;

        for (int j = 0; j < input->frames; j++) {
            if (input->numbers[i] == frameStates[j]) {
                s++;
                pageFaults--;
            }
        }

        pageFaults++;

        if ((pageFaults <= input->frames) && (s == 0)) {
            frameStates[i] = input->numbers[i];
        } else if (s == 0) {
            frameStates[(pageFaults - 1) % input->frames] = input->numbers[i];
        }

        printf("\n");
        printf("%d\t\t", input->numbers[i]);

        for (int j = 0; j < input->frames; j++) {
            if (frameStates[j] != -1)
                printf("%d\t", frameStates[j]);
            else
                printf("-\t");
        }
    }

    printf("\nTotale Page Faults:\t%d\n", pageFaults);

    pthread_exit(0);
}