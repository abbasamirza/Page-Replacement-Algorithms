#ifndef HELPERS_H
#define HELPERS_H

#include <stdbool.h>

// Define colours for readability
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define CYAN "\033[0;36m"
#define DEFAULT "\033[0m"

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
void displayTypingEffect(char*, char*);
void displayFrameState(int*, int*, int, int, char*);
void displayOutputResults(int, int, int);
void displayTextInColor(char*, char*);

// Helper/Manipulation
int convertInputStringToNumbers(int**, char*);
bool checkAllNumeric(char*);
void implementSingleAlgorithm(void*(void*), Input);
void assignDefaultFrameValues(int*, int);
bool checkPageHit(int*, int*, int, int);
int getHitIndex(int*, int*, int, int);
void OPRSearch(int*, int*, int*, int*, int, int, int);
void LRUSearch(int*, int*, int*, int*, int*, int, int);

#endif
