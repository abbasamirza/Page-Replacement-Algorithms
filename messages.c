#include "messages.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

// Input messages
char* INPUT_MSG = "Enter the reference string/page numbers (numbers should be space separated!): ";
char* INPUT_TYPE_ERROR_MSG = "Invalid input! Please enter number type only\n";

// Memory messages
char* MEMORY_ALLOCATION_FAILED = "Memory allocation failed\n";

// Thread messages
char* THREAD_CREATION_FAILED = "Error creating thread\n";
char* THREAD_JOINING_FAILED = "Error joining thread\n";

// Menu
void displayMenu() {
    system("clear");
    displayTextInColor("\t\t\t\b\b\b--- CHOOSE AN ALGORITHM ---\n", CYAN);
    printf("\t\t1. First in First Out (FIFO)\n");
    printf("\t\t2. Optimal Page Replacement (OPR)\n");
    printf("\t\t3. Least Recently Used (LRU)\n");
    printf("\t\t4. Implement All 3 Algorithms\n");
    displayTextInColor("\t\t-------------------------------------\n", BLUE);
    displayTextInColor("\t\t\t\b\b\b--- WANT TO CHANGE INPUT? ---\n", CYAN);
    printf("\t\t5. Re Enter Numbers\n");
    printf("\t\t6. Change Frame Size\n");
    printf("\t\t7. Exit\n\n");
    printf("\t\tEnter the number of the action you want to perform\n");
    displayTextInColor("\t\t\b\b\b-> ", BLUE);
}
