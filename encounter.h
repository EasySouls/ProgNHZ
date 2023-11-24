#ifndef PROGNZH_THSTAM_ENCOUNTER_H
#define PROGNZH_THSTAM_ENCOUNTER_H

#include "stdbool.h"

#include "enemies.h"
#include "io.h"

void combatEncounter(Character *player, int nrOfEnemies, bool isBossBattle);
void merchantEncounter(Character *player);

void listEnemies(Enemy **enemies, int nrOfEnemies);
void fight(Character *player, Enemy *enemy);

inline int roll() {
    return rand() % 20 + 1;
}

#endif //PROGNZH_THSTAM_ENCOUNTER_H
