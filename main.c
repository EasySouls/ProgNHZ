#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "io.h"
#include "debugmalloc.h"

int main(void) {
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    initGame();

    /* This loop is what operates the whole game.
     * The logic is that every function called will output something or ask for new inputs
     * from the user. When the called function returns, that section is done, so we can return to the menu.
     * The loop is controlled by the isRunning variable, so we just have to set that to false
     * when we want to quit or the player is dead.
     */
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

        input = askForInt(1, 2);

        if (input == 1) {
            // TODO restart the game
        }
        else if (input == 2) {
            exit(0);
        }
    }
}
