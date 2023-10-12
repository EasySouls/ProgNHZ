#include "player.h"
#include "game.h"

void SetName(Player *target, char *name) {
    strcpy(target->name, name);
}

void DisplayStats(Player *player) {
    separator();
    printf("\nName: %s (Lvl: %d)", player->name, player->level);
    printf("\nExp: %d / %d", player->exp, player->expToNext);
    printf("\nDistance traveled: %d", player->distanceTraveled);
    printf("\nHp: %d / %d", player->hp, player->maxHp);
    printf("\nMana: %d / %d", player->mana, player->maxMana);
    printf("\n%s", separatorStr);
    printf("\nStrength: %d", player->strength);
    printf("\nDexterity: %d", player->dexterity);
    printf("\nConstitution: %d", player->constitutuion);
    printf("\nIntelligence: %d", player->intelligence);
    printf("\nWisdom: %d", player->wisdom);
    printf("\nCharisma: %d", player->charisma);
    printf("\n%s", separatorStr);
    printf("Damage: %d / %d", player->damageMin, player->damageMax);
    printf("Armor: %d", player->armor);
    separator();
}

Player *NewPlayer(char *name, class class, int strength, int dexterity, int constitution, int intelligence, int wisdom,
                  int charisma) {
    return NULL;
}


