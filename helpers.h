#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

typedef struct {
    int* numbers;
    int frames, count;
} Input;

// Get input
int getInputNumbers(int**);
int getFrameSize();
void getChoice(int*, int, int);

// Display
void displayAlgorithmsName(char*);
void displayContinueMenu();
void displayTypingEffect(char*);
void displayFrameState(int*, int*, int, int);
void displayOutputResults(int, int);

// Helper/Manipulation
int convertInputStringToNumbers(int**, char*);
bool checkAllNumeric(char*);
void implementSingleAlgorithm(void*(void*), Input);
void assignDefaultFrameValues(int*, int);
bool checkPageHit(int*, int*, int, int);
void OPRSearch(int*, int*, int*, int*, int, int, int);
void LRUSearch(int*, int*, int*, int*, int*, int, int);

#endif
