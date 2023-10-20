#ifndef PROGNZH_THSTAM_INVENTORY_H
#define PROGNZH_THSTAM_INVENTORY_H

enum itemNumber {
    HEALTH_POTION,
    MANA_POTION
};

typedef struct itemStruct {
    char name[50];
    char description[100];
    int health;
    int mana;
    int quantity;
    int usesLeft;
    int id;
} Item;

typedef struct itemNodeStruct {
    Item *current;
    struct itemNodeStruct *previous;
    struct itemNodeStruct *next;
} Inventory;

void displayInvetory(Inventory *node);

Inventory* findItem(Inventory *node, enum itemNumber number);

void addItem(Inventory *invetory, enum itemNumber number);

void removeItem(Inventory *inventory, enum itemNumber number);


#endif //PROGNZH_THSTAM_INVENTORY_H
