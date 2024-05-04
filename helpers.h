#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

typedef struct {
    int* numbers;
    int frames, count;
} Input;

int getInputNumbers(int**);
int getFrameSize();
int convertInputStringToNumbers(int**, char*);
bool checkAllNumeric(char*);
void getChoice(int*, int, int);
void displayAlgorithmsName(char*);
void implementSingleAlgorithm(void*(void* ), Input);
void displayContinueMenu();
void displayTypingEffect(char*);

#endif