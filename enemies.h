#ifndef PROGNZH_THSTAM_ENEMIES_H
#define PROGNZH_THSTAM_ENEMIES_H

#include <stdlib.h>
#include "inventory.h"
#include "character.h"

typedef struct enemyStruct {
    char name[50];
    int level;

    int maxHp;
    int hp;
    int maxMana;
    int mana;

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int damageMin;
    int damageMax;
    int armor;

    Class class;

    int expAmount;

    enum itemID *lootTable;
    int lootCount;
} Enemy;

int getDamage(Enemy *enemy);

Enemy* generateEnemy(int level, Class class, char *name);

void setEnemyName(Enemy *target, char *name);

#endif //PROGNZH_THSTAM_ENEMIES_H
