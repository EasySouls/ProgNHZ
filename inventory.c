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

void addItem(Inventory *inventory, enum itemID number) {
    Inventory *previousNode;
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
            strcpy(item->name, "Health potion");
            strcpy(item->description, "Potion that heals 20 health points");
            item->health = 20;
            item->mana = 0;
            item->quantity = 1;
            item->id = number;
            break;
        case MANA_POTION:
            strcpy(item->name, "Mana potion");
            strcpy(item->description, "Potion that restores 10 mana points");
            item->health = 0;
            item->mana = 10;
            item->quantity = 1;
            item->id = number;
            break;
    }

    // If the current node is unused, assign the item
    if (inventory->current == NULL) {
        inventory->current = item;
    } else if (inventory->next == NULL) {
        // Allocate memory for the next pointer
        inventory->next = malloc(sizeof(Inventory));

        // Store location of the current node
        previousNode = inventory;

        // Move to the next node
        inventory = inventory->next;

        // Link the current node to the previous one
        inventory->previous = previousNode;

        // Assign item to the current node
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

        // Store location of the current node
        previousNode = inventory;

        // Move to the next node
        inventory = inventory->next;

        // Link the current node to the previous one
        inventory->previous = previousNode;

        // Assign item to the current node
        inventory->current = item;
        inventory->next = NULL;
    }
}

void removeItem(Inventory *inventory, enum itemID number) {
    Inventory *searchResult;
    Inventory *previous;
    Inventory *next;

    // See if item already exists.
    searchResult = findItem(inventory, number);

    // If item exists, and reduce quantity by 1.
    if (searchResult != NULL) {
        searchResult->current->quantity -= 1;

        // If reduction results in 0 quantity, remove item entirely.
        if (searchResult->current->quantity <= 0) {
            previous = searchResult->previous;
            next = searchResult->next;

            // Free the item and then the node containing it.
            free(searchResult->current);
            free(searchResult);

            // Switch linked list together.
            // We can't assign the next/previous members if the itemNode is null.
            if (previous != NULL) {
                searchResult = previous;
                searchResult->next = next;
            }
            if (next != NULL) {
                searchResult = next;
                searchResult->previous = previous;
            }
        }
    }
}

const char *getItemName(itemID item) {
    switch (item) {
        case HEALTH_POTION:
            return "Health potion";

        case MANA_POTION:
            return "Mana potion";
    }
}

// Goes through each node in the inventory and frees the consumable inside,
// and then the node itself
void freeInventoryFromMemory(Inventory *inventory) {
    Inventory *temp;

    while (inventory != NULL) {
        temp = inventory;
        inventory = inventory->next;
        free(temp->current);
        free(temp);
    }
}


