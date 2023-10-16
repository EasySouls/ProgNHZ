#include <stdio.h>
#include "io.h"

int askForInt(int min, int max) {
    while (true) {
        int num;
        printf("\nChoice: ");
        int succeded = scanf("%d", &num);
        if (succeded != 1) {
            printf("\nEnter a number please!");
            scanf("%*[^\n]"); // Basically clears the input buffer
        } else if (num > max || num < min) {
            printf("\nThe entered number was not an option! (min: %d, max: %d)", min, max);
        } else {
            return num;
        }
    }
}