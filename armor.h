#ifndef PROGNZH_THSTAM_ARMOR_H
#define PROGNZH_THSTAM_ARMOR_H

enum armorType {
    HEAD,
    CHEST,
    ARMS,
    LEGS
};

typedef struct armorStruct {
    enum armorType type;
    int value;
    char name[50];
} Armor;

Armor getNextLevelArmor(enum armorType type, int value);

#endif //PROGNZH_THSTAM_ARMOR_H
