#ifndef PROGNZH_THSTAM_ENCOUNTER_H
#define PROGNZH_THSTAM_ENCOUNTER_H

#include "enemies.h"
#include "io.h"

typedef struct combatEncounterStruct {
    Enemy *enemies;
    int encounterLevel;
} Encounter;

void combatEncounter(Character *player, int nrOfEnemies);

void listEnemies(Enemy **enemies, int nrOfEnemies);
void fight(Character *player, Enemy *enemy);
int roll();

#endif //PROGNZH_THSTAM_ENCOUNTER_H
