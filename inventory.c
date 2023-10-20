#include "inventory.h"

#include "debugmalloc.h"

void displayInvetory(Inventory *node) {
    while (node->current != NULL) {
        printf("Name: %s\n", node->current->name);
        printf("Description: %s\n", node->current->description);
        if (node->current->health > 0)
            printf("Health: %d\n", node->current->health);
        if (node->current->mana > 0)
            printf("Mana: %d\n", node->current->mana);
        printf("Quantity: %d\n", node->current->quantity);
        printf("Uses Left: %d\n", node->current->usesLeft);

        // If the node points to another node, go to it and print
        // it's item. Otherwise, end loop
        if (node->next != NULL) {
            node = node->next;
        } else {
            return;
        }
    }

    // Inventory pointer is null, there are no items
    printf("Inventory is empty.\n");
}

Inventory *findItem(Inventory *node, enum itemNumber number) {
    if (node == NULL) {
        return NULL;
    }

    while (node->current != NULL) {
        // Compare that item's id to our number
        // If it's a match, return the address of that node
        if (node->current->id == number) {
            return node;
        }

        // If the current item doesn't match and there is
        // another node, move to it
        if (node->next != NULL) {
            node = node->next;
        } else {
            return NULL; // List ends
        }
    }

    return NULL; // List is empty
}

void addItem(Inventory *inventory, enum itemNumber number) {
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
    // Allocate memory for it and increase size of the linked list
    Item *item = malloc(sizeof(Item));

    // Assign values to our item based on the enum parameter
    switch (number) {
        case HEALTH_POTION:
            strcpy(item->name, "Health potion");
            strcpy(item->description, "Potion that heals 20 health points");
            item->health = 20;
            item->mana = 0;
            item->usesLeft = 1;
            item->quantity = 1;
            item->id = number;
            break;
        case MANA_POTION:
            strcpy(item->name, "Mana potion");
            strcpy(item->description, "Ption that restores 10 mana points");
            item->health = 0;
            item->mana = 10;
            item->usesLeft = 1;
            item->quantity = 1;
            item->id = number;
            break;
    }

    // Now we have to store it in our linked list
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
    }
}

void removeItem(Inventory *inventory, enum itemNumber number) {
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
