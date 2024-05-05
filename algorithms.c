#include "algorithms.h"
#include "helpers.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void* FIFO(void* arg) {
    Input* input = (Input*)arg; // Destructure input struct
    int* frame = malloc(input->frames * sizeof(int)); // Create frame
    int pageFaults = 0;

    assignDefaultFrameValues(frame, input->frames);

    for (int i = 0; i < input->count; i++) {
        // To check if page is present already or not
        bool pageInFrame = false;

        if (checkPageHit(input->numbers, frame, input->frames, i)) {
            pageInFrame = true;
            pageFaults--;
        }

        pageFaults++;

        // Check if there is empty space in frame and page is not in frame (page fault/miss)
        if ((pageFaults <= input->frames) && (!pageInFrame)) {
            frame[i] = input->numbers[i];
        } else if (!pageInFrame) { // Check if page is not frame but there is no empty space
            frame[(pageFaults - 1) % input->frames] = input->numbers[i];
        }

        displayFrameState(input->numbers, frame, input->frames, i);
    }

    displayOutputResults(input->count - pageFaults, pageFaults);

    pthread_exit(0);
}

void* OPR(void* arg) {
    Input* input = (Input*)arg; // Destructure input struct
    int* frame = malloc(input->frames * sizeof(int));   // Create frame
    int index = -1, pageFaults = 0;
    bool full = false;

    assignDefaultFrameValues(frame, input->frames);

    for (int i = 0; i < input->count; i++) {
        // Check if page is already present in frame or not
        if (!checkPageHit(input->numbers, frame, input->frames, i)) {
            if (!full) {
                // Check which frame cell is empty
                index = (index + 1) % input->frames;
                frame[index] = input->numbers[i];
                pageFaults++;

                // Check whether frame is full
                if (i == input->frames - 1) {
                    full = true;
                }
            } else {
                // If frame is full
                int pos = -1, index = -1;

                // Search algorithm to check if the incoming number is occurring in the input string ahead or not
                OPRSearch(input->numbers, frame, &pos, &index, input->frames, input->count, i);

                pageFaults++;
                frame[index] = input->numbers[i];
            }
        }

        displayFrameState(input->numbers, frame, input->frames, i);
    }

    displayOutputResults(input->count - pageFaults, pageFaults);

    pthread_exit(0);
}

void* LRU(void* arg) {
    Input* input = (Input*)arg; // Destructure input struct
    int* frame = malloc(input->frames * sizeof(int));   // Create frame
    int* distance = malloc(input->frames * sizeof(int));
    int pageFaults = 0, occupied = 0;

    assignDefaultFrameValues(frame, input->frames);

    for (int i = 0; i < input->count; i++) {
        if (!checkPageHit(input->numbers, frame, input->frames, i)) {
            if (occupied < input->frames) {
                frame[occupied] = input->numbers[i];
                pageFaults++;
                occupied++;
            } else {
                int max = INT_MIN, index;

                LRUSearch(input->numbers, frame, distance, &max, &index, input->frames, i);

                frame[index] = input->numbers[i];
                pageFaults++;
            }
        }

        displayFrameState(input->numbers, frame, input->frames, i);
    }

    displayOutputResults(input->count - pageFaults, pageFaults);

    pthread_exit(0);
}
