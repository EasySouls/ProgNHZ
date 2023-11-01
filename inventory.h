#ifndef PROGNZH_THSTAM_INVENTORY_H
#define PROGNZH_THSTAM_INVENTORY_H

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
} Consumable;

typedef struct itemNodeStruct {
    Consumable *current;
    struct itemNodeStruct *previous;
    struct itemNodeStruct *next;
} Inventory;

void displayInventory(Inventory *inventory);
void addItem(Inventory *invetory, enum itemID number);
void removeItem(Inventory *inventory, enum itemID number);

Inventory* findItem(Inventory *inventory, enum itemID number);

const char* getItemName(itemID item);

void freeInventoryFromMemory(Inventory *inventory);

#endif //PROGNZH_THSTAM_INVENTORY_H
