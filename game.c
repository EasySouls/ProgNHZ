#include "game.h"

bool isRunning = false;
bool quit = false;
int input = 0;

void initGame() {
    isRunning = true;
}

void mainMenu() {
    separator();
    printf("\nMenu");
    printf("\n[1]: Travel");
    printf("\n[2]: Rest");
    printf("\n[3]: Level up");
    printf("\n[4]: Save character");
    printf("\n[5]: Load character");
    printf("\n[9]: Exit game");

    askForInput();

    while (input < 1 || (input > 5 && input != 9)) {
        inputError();
    }

    switch (input) {
        case 1:
            travel();
            break;
        case 2:
            rest();
            break;
        case 3:
            levelUp();
            break;
        case 4:
            saveCharacter();
            break;
        case 5:
            loadCharacter();
            break;
        case 9:
            exitGame();
            break;
        default:
            printf("\nMr. Developer didn't think this could happen, but this proves that correct error handling is neccessary");
            inputError();
            break;
    }
}

void travel() {

}

void rest() {

}

void levelUp() {

}

void saveCharacter() {

}

void loadCharacter() {

}

void exitGame() {
    isRunning = false;
}

// Utility functions

void askForInput() {
    printf("\nAction: ");
    scanf("%d", &input);
}

void inputError() {
    printf("\nIncorrect input. Please choose again!");
    askForInput();
}

void separator() {
    printf("\n*---------------------------------*\n");
}











