#include "inventory.h"

#include "debugmalloc.h"

void displayInventory(Inventory *inventory) {
    while (inventory->current != NULL) {
        printf("Name: %s\n", inventory->current->name);
        printf("Description: %s\n", inventory->current->description);
        if (inventory->current->health > 0)
            printf("Health: %d\n", inventory->current->health);
        if (inventory->current->mana > 0)
            printf("Mana: %d\n", inventory->current->mana);
        printf("Quantity: %d\n", inventory->current->quantity);

        // If the inventory points to another inventory, go to it and print
        // it's item. Otherwise, end loop
        if (inventory->next != NULL) {
            inventory = inventory->next;
        } else {
            return;
        }
    }

    // Inventory pointer is null, there are no items
    printf("Inventory is empty.\n");
}

Inventory *findItem(Inventory *inventory, enum itemID number) {
    if (inventory == NULL) {
        return NULL;
    }

    while (inventory->current != NULL) {
        // Compare that item's id to our number
        // If it's a match, return the address of that node
        if (inventory->current->id == number) {
            return inventory;
        }

        // If the current item doesn't match and there is
        // another node, move to it
        if (inventory->next != NULL) {
            inventory = inventory->next;
        } else {
            return NULL; // List ends
        }
    }

    return NULL; // List is empty
}

// If the item is already present in the inventory, increases its quantity by one,
// otherwise adds the item to the linked list
// Automatically allocates memory for the newly added item
void addItem(Inventory *inventory, enum itemID number) {
    Inventory *searchResult;

    // See if item already exists
    searchResult = findItem(inventory, number);
    if (searchResult != NULL) {
        // Increase quantity by one and return from function
        searchResult->current->quantity += 1;
        return;
    }

    // Generate item if it doesn't exist
    Consumable *item = malloc(sizeof(Consumable));

    // Assign values to our item based on the enum parameter
    switch (number) {
        case HEALTH_POTION:
            strcpy(item->name, "Health Potion");
            strcpy(item->description, "Potion that heals 20 health points");
            item->health = 20;
            item->mana = 0;
            item->damage = 0;
            item->quantity = 1;
            item->id = number;
            item->use = restoreHp;
            break;
        case MANA_POTION:
            strcpy(item->name, "Mana Potion");
            strcpy(item->description, "Potion that restores 10 mana points");
            item->health = 0;
            item->mana = 10;
            item->damage = 0;
            item->quantity = 1;
            item->id = number;
            item->use = restoreMana;
            break;
        case DEMON_OIL:
            strcpy(item->name, "Demon Oil");
            strcpy(item->description, "Grants temporary damage buff");
            item->health = 0;
            item->mana = 0;
            item->damage = 3;
            item->quantity = 1;
            item->id = number;
            item->use = addDamage;
            break;
        case LARGE_HEALTH_POTION:
            strcpy(item->name, "Large Health Potion");
            strcpy(item->description, "Potion that heals 40 health points");
            item->health = 40;
            item->mana = 0;
            item->damage = 0;
            item->quantity = 1;
            item->id = number;
            item->use = restoreHp;
            break;
        case LARGE_MANA_POTION:
            strcpy(item->name, "Large Mana Potion");
            strcpy(item->description, "Potion that restores 25 mana points");
            item->health = 0;
            item->mana = 25;
            item->damage = 0;
            item->quantity = 1;
            item->id = number;
            item->use = restoreMana;
            break;
        case HELLFIRE_OIL:
            strcpy(item->name, "Hellfire Oil");
            strcpy(item->description, "Grants greater temporary damage buff");
            item->health = 0;
            item->mana = 0;
            item->damage = 6;
            item->quantity = 1;
            item->id = number;
            item->use = addDamage;
            break;
    }

    // If the current node is unused, assign the item
    if (inventory->current == NULL) {
        inventory->current = item;
    } else if (inventory->next == NULL) {
        inventory->next = malloc(sizeof(Inventory));

        inventory = inventory->next;

        inventory->current = item;
        inventory->next = NULL;
    } else {
        // If the current node is occupied, search for the last node
        // The last node's "next" pointer will be null
        while (inventory->next != NULL) {
            inventory = inventory->next;
        }
        // Allocate memory for the next pointer
        inventory->next = malloc(sizeof(Inventory));

        // Move to the next node
        inventory = inventory->next;

        // Assign item to the current node
        inventory->current = item;
        inventory->next = NULL;
    }
}

void removeItem(Inventory *inventory, enum itemID number) {
    Inventory *searchResult;
    Inventory *next;

    // See if item already exists.
    searchResult = findItem(inventory, number);

    // If item exists, and reduce quantity by 1.
    if (searchResult != NULL) {
        searchResult->current->quantity -= 1;

        // If reduction results in 0 quantity, remove item entirely.
        if (searchResult->current->quantity <= 0) {
            next = searchResult->next;

            // Free the item and then the node containing it.
            free(searchResult->current);
            free(searchResult);

            if (next != NULL) {
                searchResult = next;
            }
        }
    }
}

const char *getItemName(itemID item) {
    switch (item) {
        case HEALTH_POTION:
            return "Health Potion";
        case MANA_POTION:
            return "Mana Potion";
        case DEMON_OIL:
            return "Demon Oil";
        case LARGE_HEALTH_POTION:
            return "Large Health Potion";
        case LARGE_MANA_POTION:
            return "Large Mana Potion";
        case HELLFIRE_OIL:
            return "Hellfire Oil";
    }
    return "";
}

Inventory* initInventory() {
    Inventory *inventory = malloc(sizeof(Inventory));
    inventory->current = NULL;
    inventory->next = NULL;
    return inventory;
}

// Goes through each node in the inventory and frees the consumable inside,
// and then the node itself
void freeInventoryFromMemory(Inventory *inventory) {
    Inventory *temp;

    while (inventory != NULL) {
        temp = inventory;
        inventory = inventory->next;
        if (temp->current != NULL) {
            free(temp->current);
        }
        free(temp);
    }
}

int listItems(Inventory *inventory) {
    int count = 0;
    while (inventory != NULL) {
        Consumable *current = inventory->current;
        printf("\n[%d]: %s, Quantity: %d", ++count, current->name, current->quantity);
        printf("\n      %s", current->description);
        inventory = inventory->next;
    }
    return count;
}

int listMerchantItems(Inventory *inv) {
    int count = 0;
    while (inv != NULL) {
        Consumable *current = inv->current;
        printf("\n[%d]: %s, Quantity: %d, Price: %d gold",
               ++count, current->name, current->quantity, getItemPrice(current->id));
        inv = inv->next;
    }
    return count;
}

Consumable *getItemAtPosition(int position, Inventory *inventory) {
    for (int i = 0; i < position - 1; ++i) {
        inventory = inventory->next;
    }
    return inventory->current;
}

int getItemPrice(itemID item) {
    return consumablePrices[item];
}




