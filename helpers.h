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

#endif