#include "player.h"


void SetName(Player *target, char *name) {
    strcpy(target->name, name);
}

void DisplayStats(Player *player) {
    printf("\nName: %s (Lvl: %d)", player->name, player->level);
    printf("\nExp: %d / %d", player->exp, player->expToNext);
    printf("\nDistance traveled: %d", player->distanceTraveled);
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
}

Player *NewPlayer(char *name, class class, int strength, int dexterity, int constitution, int intelligence, int wisdom,
                  int charisma) {
    // Allocate memory to player pointer
    Player *tempPlayer = malloc(sizeof(Player));
    SetName(tempPlayer, name);

    // Assign chosen stats
    tempPlayer->strength = strength;
    tempPlayer->dexterity = dexterity;
    tempPlayer->constitutuion = constitution;
    tempPlayer->intelligence = intelligence;
    tempPlayer->wisdom = wisdom;
    tempPlayer->charisma = charisma;

    tempPlayer->distanceTraveled = 0;
    tempPlayer->exp = 0;
    tempPlayer->expToNext = 200;
    tempPlayer->level = 1;

    // Assign stats based on the chosen class
    switch (class) {
        case WARRIOR:
            tempPlayer->maxHp = (constitution * 3) + 20;
            tempPlayer->maxMana = 10;
            tempPlayer->class = WARRIOR;
            tempPlayer->armor = 2;
            break;
        case RANGER:
            tempPlayer->maxHp = (constitution * 2) + 15;
            tempPlayer->maxMana = 15;
            tempPlayer->class = RANGER;
            tempPlayer->armor = 1;
            break;
        case MAGE:
            tempPlayer->maxHp = (constitution * 3) + 20;
            tempPlayer->maxMana = 10;
            tempPlayer->class = WARRIOR;
            tempPlayer->armor = 0;
            break;
    }

    // Assign stats calculated from the base stats
    tempPlayer->hp = tempPlayer->maxHp;
    tempPlayer->mana = tempPlayer->maxMana;
    tempPlayer->damageMin = strength * 2;
    tempPlayer->damageMax = (strength * 2) + 3;
    tempPlayer->armor += 8 + (dexterity / 2);
}


