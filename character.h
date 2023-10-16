#ifndef PROGNZH_THSTAM_CHARACTER_H
#define PROGNZH_THSTAM_CHARACTER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "gameProperties.h"

Character* newCharacter(char name[50], Class class);

void setName(Character *target, char name[50]);
void displayStats(Character *player);

const char* getAttributeName(int index);
int getModifier(int attr);

#endif //PROGNZH_THSTAM_CHARACTER_H
