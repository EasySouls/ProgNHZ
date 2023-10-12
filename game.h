#ifndef PROGNZH_THSTAM_GAME_H
#define PROGNZH_THSTAM_GAME_H
#include <stdbool.h>
#include <stdio.h>

// Game logic

extern bool isRunning;
extern bool quit;
extern int input;

// Gameplay functions

void initGame();
void mainMenu();

void travel();
void rest();
void levelUp();
void saveCharacter();
void loadCharacter();
void exitGame();

// Utility
void askForInput();
void inputError();
void separator();
extern char separatorStr[];

#endif //PROGNZH_THSTAM_GAME_H
