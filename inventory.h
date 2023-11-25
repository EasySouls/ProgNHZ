#ifndef PROGNZH_THSTAM_INVENTORY_H
#define PROGNZH_THSTAM_INVENTORY_H

#include "consumable.h"

typedef struct itemNodeStruct {
    Consumable *current;
    struct itemNodeStruct *next;
} Inventory;

Inventory* initInventory();

void displayInventory(Inventory *inventory);
void addItem(Inventory *inventory, itemID number);
void removeItem(Inventory *inventory, itemID number);
int listItems(Inventory *inventory);
Consumable* getItemAtPosition(int position, Inventory *inventory);

Inventory* findItem(Inventory *inventory, itemID number);

const char* getItemName(itemID item);
int getItemPrice(itemID item);
int listMerchantItems(Inventory *inv);

void freeInventoryFromMemory(Inventory *inventory);

#endif //PROGNZH_THSTAM_INVENTORY_H
