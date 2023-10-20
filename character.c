#include "character.h"
#include "debugmalloc.h"

void setName(Character *target, char *name) {
    strcpy(target->name, name);
}

void displayStats(Character *player) {
    printf("\nName: %s (Lvl: %d)", player->name, player->level);
    printf("\nExp: %d / %d", player->exp, player->expToNext);
    printf("\nDistance traveled: %d", player->distanceTraveled);
    printf("\nGold: %d", player->gold);
    printf("\nHp: %d / %d", player->hp, player->maxHp);
    printf("\nMana: %d / %d", player->mana, player->maxMana);
    printf("\nStrength: %d", player->strength);
    printf("\nDexterity: %d", player->dexterity);
    printf("\nConstitution: %d", player->constitution);
    printf("\nIntelligence: %d", player->intelligence);
    printf("\nWisdom: %d", player->wisdom);
    printf("\nCharisma: %d", player->charisma);
    printf("\nDamage: %d - %d", player->damageMin, player->damageMax);
    printf("\nArmor: %d", player->armor);
    printf("\n");
}

Character *newCharacter(char *name, Class class) {
    // Allocate memory to player pointer
    Character *tempPlayer = malloc(sizeof(Character));
    setName(tempPlayer, name);

    // Assign stats based on the chosen Class
    switch (class) {
        case WARRIOR:
            tempPlayer->class = WARRIOR;
            tempPlayer->strength = 16;
            tempPlayer->dexterity = 12;
            tempPlayer->constitution = 15;
            tempPlayer->intelligence = 8;
            tempPlayer->wisdom = 9;
            tempPlayer->charisma = 13;
            break;
        case RANGER:
            tempPlayer->class = RANGER;
            tempPlayer->strength = 14;
            tempPlayer->dexterity = 18;
            tempPlayer->constitution = 12;
            tempPlayer->intelligence = 10;
            tempPlayer->wisdom = 13;
            tempPlayer->charisma = 12;
            break;
        case MAGE:
            tempPlayer->class = WARRIOR;
            tempPlayer->strength = 8;
            tempPlayer->dexterity = 11;
            tempPlayer->constitution = 8;
            tempPlayer->intelligence = 17;
            tempPlayer->wisdom = 15;
            tempPlayer->charisma = 14;
            break;
    }

    // Assign stats calculated from the base stats
    tempPlayer->level = 1;
    tempPlayer->maxHp = (tempPlayer->level * 20) + 5 * getModifier(tempPlayer->constitution);

    int possibleMana = 5 + 3 * getModifier(tempPlayer->intelligence) + 2 * getModifier(tempPlayer->wisdom);
    if (possibleMana > 5) {
        tempPlayer->maxMana = 5 + 3 * getModifier(tempPlayer->intelligence) + 2 * getModifier(tempPlayer->wisdom);
    } else {
        tempPlayer->maxMana = 5;
    }

    tempPlayer->hp = tempPlayer->maxHp;
    tempPlayer->mana = tempPlayer->maxMana;
    tempPlayer->damageMin = getModifier(tempPlayer->strength) * 4;
    tempPlayer->damageMax = getModifier(tempPlayer->strength) * 5;
    tempPlayer->armor = 10 + getModifier(tempPlayer->dexterity);

    // Assign the rest of the stats
    tempPlayer->distanceTraveled = 0;
    tempPlayer->exp = 0;
    tempPlayer->expToNext = 200;
    tempPlayer->level = 1;
    tempPlayer->gold = 100;
    tempPlayer->inventory = malloc(sizeof(Inventory));

    return tempPlayer;
}

const char* getAttributeName(int index) {
    const char* attributeNames[] = {"Strength", "Dexterity", "Constitution",
                                    "Intelligence", "Wisdom", "Charisma"};
    return attributeNames[index];
}

int getModifier(int attr) {
    return (attr - 10) / 2;
}

Character *calcStats(CharacterBase *c) {
    Character *temp = malloc(sizeof(Character));

    setName(temp, c->name);
    temp->level = c->level;
    temp->exp = c->exp;
    temp->expToNext = (c->level - 1) * 500 + 200;
    temp->distanceTraveled = c->distanceTraveled;
    temp->gold = c->gold;

    temp->class = c->class;
    temp->maxHp = (c->level * 20) + 5 * getModifier(c->constitution);
    temp->hp = c->hp;

    int possibleMana = 5 + 3 * getModifier(c->intelligence) + 2 * getModifier(c->wisdom);
    if (possibleMana > 5) {
        temp->maxMana = 5 + 3 * getModifier(c->intelligence) + 2 * getModifier(c->wisdom);
    } else {
        temp->maxMana = 5;
    }
    temp->mana = c->mana;

    temp->strength = c->strength;
    temp->dexterity = c->dexterity;
    temp->constitution = c->constitution;
    temp->intelligence = c->intelligence;
    temp->wisdom = c->wisdom;
    temp->charisma = c->charisma;

    temp->damageMin = getModifier(c->strength) * 4;
    temp->damageMax = getModifier(c->strength) * 5;
    temp->armor = 10 + getModifier(c->dexterity);

    temp->inventory = malloc(sizeof(Inventory));

    return temp;
}


