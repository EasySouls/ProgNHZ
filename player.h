#ifndef PROGNZH_THSTAM_PLAYER_H
#define PROGNZH_THSTAM_PLAYER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gameProperties.h"

void SetName(Player *target, char name[50]);
void DisplayStats(Player *player);
Player* NewPlayer(char name[50],class class, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);

#endif //PROGNZH_THSTAM_PLAYER_H
