#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    initGame();

    while (isRunning) {
        mainMenu();
    }

    if (quit) {
        exit(0);
    }
    else {
        printf("\nYou died. Would you like to try again?");
        printf("\n[1]: Yes");
        printf("\n[2]: Nope");

        askForInput();
        while (input < 1 || input > 2) {
            inputError();
        }


        if (input == 1) {
            // TODO restart the game
        }
        else if (input == 2) {
            exit(1);
        }
    }
}
