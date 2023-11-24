#ifndef PROGNZH_THSTAM_GAME_H
#define PROGNZH_THSTAM_GAME_H
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "character.h"
#include "io.h"
#include "encounter.h"
#include "inventory.h"

extern const char charactersFile[];

// Game logic

extern bool isRunning;
extern bool quit;
extern int input;

// Characters
extern Character *character;

// Gameplay functions

void initGame();
void mainMenu();

Character* createCharacter();

void travel();
void rest();
void levelUp();
void printStats();
void equippedItems(Character *player);
void saveCharacter(Character *c);
void loadCharacter();
void saveAndLoadSubmenu();
void exitGame();

#endif //PROGNZH_THSTAM_GAME_H
