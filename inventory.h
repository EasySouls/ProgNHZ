#ifndef PROGNZH_THSTAM_INVENTORY_H
#define PROGNZH_THSTAM_INVENTORY_H

#include "consumable.h"

typedef struct itemNodeStruct {
    Consumable *current;
    struct itemNodeStruct *next;
} Inventory;

Inventory* initInventory();

void displayInventory(Inventory *inventory);
void addItem(Inventory *inventory, enum itemID number);
void removeItem(Inventory *inventory, enum itemID number);

Inventory* findItem(Inventory *inventory, enum itemID number);

const char* getItemName(itemID item);

void freeInventoryFromMemory(Inventory *inventory);

#endif //PROGNZH_THSTAM_INVENTORY_H
