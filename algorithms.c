#include "algorithms.h"
#include "helpers.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void* FIFO(void* arg) {
    Input* input = (Input*)arg;
    int* frameStates = malloc(input->frames * sizeof(int));
    int pageFaults = 0;

    printf("\tIncoming\t");

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
        printf("\t%d\t\t", input->numbers[i]);

        for (int j = 0; j < input->frames; j++) {
            if (frameStates[j] != -1)
                printf("%d\t", frameStates[j]);
            else
                printf("-\t");
        }
    }

    printf("\n\n\tTotal Page Faults: %d\n", pageFaults);

    pthread_exit(0);
}

int checkHit(int incomingPage, int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        if (incomingPage == queue[i]) {
            return 1;
        }
    }

    return 0;
}

void printFrame(int queue[], int occupied) {
    for (int i = 0; i < occupied; i++) {
        printf("%d\t", queue[i]);
    }
}

void* OPR(void* arg) {
    Input* input = (Input*)arg;
    int* frameStates = malloc(input->frames * sizeof(int));
    int index = -1, pageFaults = 0;
    bool full = false;

    printf("\tIncoming\t");

    for (int i = 0; i < input->frames; i++) {
        printf("Frame %d\t", i + 1);
        frameStates[i] = -1;
    }
    printf("\n");

    for (int i = 0; i < input->count; i++) {
        int s = input->numbers[i];
        bool flag = false;

        for (int j = 0; j < input->frames; j++) {
            if (s == frameStates[j]) {
                flag = true;
                break;
            }
        }

        if (flag) {
            printf("\n\t%d\t\t", s);

            for (int j = 0; j < input->frames; j++) {
                printf("%d\t", frameStates[j]);
            }
        } else {
            if (full == 0) {
                index = (index + 1) % input->frames;
                frameStates[index] = s;
                pageFaults++;

                printf("\n\t%d\t\t", s);

                for (int j = 0; j < input->frames; j++) {
                    printf("%d\t", frameStates[j]);
                }

                if (i == input->frames - 1) {
                    full = true;
                }
            } else {
                int pos = -1, index = -1;

                for (int j = 0; j < input->frames; j++) {
                    bool found = false;

                    for (int k = i + 1; k < input->count; k++) {
                        if (frameStates[j] == input->numbers[k]) {
                            found = true;

                            if (pos < k) {
                                pos = k;
                                index = j;
                            }

                            break;
                        }
                    }

                    if (!found) {
                        pos = input->count;
                        index = j;
                    }
                }

                pageFaults++;
                frameStates[index] = s;

                printf("\n\t%d\t\t", s);

                for (int j = 0; j < input->frames; j++) {
                    printf("%d\t", frameStates[j]);
                }
            }
        }
    }

    printf("\n\nPage Faults: %d\n", pageFaults);

    pthread_exit(0);
}

void* LRU(void* arg) {
    Input* input = (Input*)arg;
    int* frameStates = malloc(input->frames * sizeof(int));
    int* distance = malloc(input->frames * sizeof(int));
    int pageFaults = 0, occupied = 0;

    printf("\tIncoming\t");

    for (int i = 0; i < input->frames; i++) {
        printf("Frame %d\t", i + 1);
        frameStates[i] = -1;
    }
    printf("\n");

    for (int i = 0; i < input->count; i++) {
        printf("\n\t%d\t\t", input->numbers[i]);

        if (checkHit(input->numbers[i], frameStates, occupied)) {
            printFrame(frameStates, occupied);
        } else if (occupied < input->frames) {
            frameStates[occupied] = input->numbers[i];
            pageFaults++;
            occupied++;

            printFrame(frameStates, occupied);
        } else {
            int max = INT_MIN, index;

            for (int j = 0; j < input->frames; j++) {
                distance[j] = 0;

                for (int k = i - 1; k >= 0; k--) {
                    ++distance[j];

                    if (frameStates[j] == input->numbers[k]) {
                        break;
                    }
                }

                if (distance[j] > max) {
                    max = distance[j];
                    index = j;
                }
            }

            frameStates[index] = input->numbers[i];
            printFrame(frameStates, occupied);
            pageFaults++;
        }
    }

    printf("\n\nPage Faults: %d\n", pageFaults);

    pthread_exit(0);
}