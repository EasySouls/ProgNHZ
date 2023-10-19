#ifndef PROGNZH_THSTAM_GAMEPROPERTIES_H
#define PROGNZH_THSTAM_GAMEPROPERTIES_H

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
    int armor;
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

    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;
} CharacterBase;


#endif //PROGNZH_THSTAM_GAMEPROPERTIES_H
