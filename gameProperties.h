#ifndef PROGNZH_THSTAM_GAMEPROPERTIES_H
#define PROGNZH_THSTAM_GAMEPROPERTIES_H

typedef enum ClassEnum {
    WARRIOR,
    RANGER,
    MAGE
} class;

typedef struct playerStructure {
    char name[50];
    int level;
    int exp;
    int expToNext;
    int distanceTraveled;

    int maxHp;
    int hp;
    int maxMana;
    int mana;

    class class;

    int strength;
    int dexterity;
    int constitutuion;
    int intelligence;
    int wisdom;
    int charisma;

    int damageMin;
    int damageMax;
    int armor;
} Player;


#endif //PROGNZH_THSTAM_GAMEPROPERTIES_H
