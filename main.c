#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    initGame();
    Player *player = NewPlayer("Csanad", WARRIOR, 15, 11, 14, 8, 6, 12);
    DisplayStats(player);

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
