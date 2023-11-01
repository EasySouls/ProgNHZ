#ifndef PROGNZH_THSTAM_CHARACTER_H
#define PROGNZH_THSTAM_CHARACTER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inventory.h"
#include "armor.h"

typedef enum ClassEnum {
    WARRIOR,
    RANGER,
    MAGE
} Class;

typedef struct playerStructure {
    char name[50];
    int level;
    int exp;
    int expToNext;
    int distanceTraveled;
    int gold;

    Inventory *inventory;
    Armor armors[4];

    int maxHp;
    int hp;
    int maxMana;
    int mana;

    Class class;

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int damageMin;
    int damageMax;
    int baseArmorClass;

} Character;

typedef struct characterBase {
    char name[50];
    int level;
    int exp;
    int distanceTraveled;
    int gold;

    int hp;
    int mana;

    Class class;
    Armor armors[4];

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
} CharacterBase;

Character* newCharacter(char name[50], Class class);
Character* calcStats(CharacterBase *c);

void setName(Character *target, char name[50]);
void displayStats(Character *player);

const char* getAttributeName(int index);
int getModifier(int attr);
int getArmorClass(Character *player);
int getPlayerDamage(Character *player);

#endif //PROGNZH_THSTAM_CHARACTER_H
