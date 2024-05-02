#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int* numbers = NULL;

    if (argc > 1) {
        numbers = (int*)calloc(argc - 1, sizeof(int));

        for (int i = 0; i < argc - 1; i++) {
            numbers[i] = atoi(argv[i + 1]);
        }
    } else {
        int count = getInputNumbers(&numbers);
    }

    return 0;
}
