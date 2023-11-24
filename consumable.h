#ifndef PROGNZH_THSTAM_CONSUMABLE_H
#define PROGNZH_THSTAM_CONSUMABLE_H

struct playerStructure;

typedef enum itemID {
    HEALTH_POTION,
    MANA_POTION
} itemID;

typedef struct consumableStruct {
    char name[50];
    char description[100];
    int health;
    int mana;
    int quantity;
    enum itemID id;

    void (*use)(struct playerStructure *target, struct consumableStruct *self);
} Consumable;

// Use item functions for the struct's function pointer

void restoreHp(struct playerStructure *target, Consumable *self);
void restoreMana(struct playerStructure *target, Consumable *self);

#endif //PROGNZH_THSTAM_CONSUMABLE_H
