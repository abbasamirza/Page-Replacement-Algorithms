#include "messages.h"
#include <stdio.h>
#include <stdlib.h>

// Input messages
const char* INPUT_MSG = "Enter the reference string/page numbers (numbers should be space separated!): ";
const char* INPUT_TYPE_ERROR_MSG = "Invalid input! Please enter number type only\n";

// Memory messages
const char* MEMORY_ALLOCATION_FAILED = "Memory allocation failed\n";

// Thread messages
const char* THREAD_CREATION_FAILED = "Error creating thread\n";
const char* THREAD_JOINING_FAILED = "Error joining thread\n";

// Menu
void displayMenu() {
    system("clear");
    printf("\t\t\t\b\b\b--- CHOOSE AN ALGORITHM ---\n");
    printf("\t\t1. First in First Out (FIFO)\n");
    printf("\t\t2. Optimal Page Replacement (OPR)\n");
    printf("\t\t3. Least Recently Used (LRU)\n");
    printf("\t\t4. Implement All 3 Algorithms\n");
    printf("\t\t-------------------------------------\n");
    printf("\t\t\t\b\b\b--- WANT TO CHANGE INPUT? ---\n");
    printf("\t\t5. Re Enter Numbers\n");
    printf("\t\t6. Change Frame Size\n");
    printf("\t\t7. Exit\n\n");
    printf("\t\tEnter the number of the action you want to perform\n");
    printf("\t\t\b\b\b-> ");
}