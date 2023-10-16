#include "character.h"


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
    printf("\nConstitution: %d", player->constitutuion);
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
            tempPlayer->maxHp = 40;
            tempPlayer->maxMana = 10;
            tempPlayer->class = WARRIOR;
            tempPlayer->strength = 16;
            tempPlayer->dexterity = 12;
            tempPlayer->constitutuion = 15;
            tempPlayer->intelligence = 8;
            tempPlayer->wisdom = 9;
            tempPlayer->charisma = 13;
            break;
        case RANGER:
            tempPlayer->maxHp = 32;
            tempPlayer->maxMana = 15;
            tempPlayer->class = RANGER;
            tempPlayer->strength = 14;
            tempPlayer->dexterity = 18;
            tempPlayer->constitutuion = 12;
            tempPlayer->intelligence = 10;
            tempPlayer->wisdom = 13;
            tempPlayer->charisma = 12;
            break;
        case MAGE:
            tempPlayer->maxHp = 28;
            tempPlayer->maxMana = 10;
            tempPlayer->class = WARRIOR;
            tempPlayer->strength = 8;
            tempPlayer->dexterity = 11;
            tempPlayer->constitutuion = 8;
            tempPlayer->intelligence = 17;
            tempPlayer->wisdom = 15;
            tempPlayer->charisma = 14;
            break;
    }

    // Assign stats calculated from the base stats
    tempPlayer->hp = tempPlayer->maxHp;
    tempPlayer->mana = tempPlayer->maxMana;
    tempPlayer->damageMin = tempPlayer->strength * 2;
    tempPlayer->damageMax = (tempPlayer->strength * 2) + 3;
    tempPlayer->armor += 10 + getModifier(tempPlayer->dexterity);

    // Assign the rest of the stats
    tempPlayer->distanceTraveled = 0;
    tempPlayer->exp = 0;
    tempPlayer->expToNext = 200;
    tempPlayer->level = 1;
    tempPlayer->gold = 100;

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


