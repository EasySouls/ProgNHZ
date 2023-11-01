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

#endif //PROGNZH_THSTAM_ARMOR_H
