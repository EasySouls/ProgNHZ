#include "encounter.h"
#include "debugmalloc.h"

int roll() {
    return rand() % 20 + 1;
}

void combatEncounter(Character *player, int nrOfEnemies, bool isBossBattle) {
    // Initiate the enemies
    Enemy **enemies = malloc(nrOfEnemies * sizeof(Enemy));
    int encounterLevel = player->level;
    int encounterExpAmount = encounterLevel * 100;

    for (int i = 0; i < nrOfEnemies; ++i) {
        int class = rand() % 3;
        // If the current encounter is a boss batle, the first enemy
        // will be one level above the player
        if (isBossBattle && i == 0) {
            enemies[i] = generateEnemy(encounterLevel + 1, class, "Boss");
        } else {
            enemies[i] = generateEnemy(encounterLevel, class, "");
        }
    }

    int playerRoll;
    int enemyRoll;
    int choice;
    int encounterDifficulty = 8 + player->level;

    bool playerTurn = true;
    bool escaped = false;
    bool hasWon = false;

    while (!hasWon && player->hp > 0 && !escaped) {

        // The player's turn
        if (playerTurn) {
            printf("\n%s, HP: %d / %d\n", player->name, player->hp, player->maxHp);
            printf("[1]: Attack\n");
            printf("[2]: Use item\n");
            printf("[3]: Escape\n");

            choice = askForInt(1, 3);
            int itemCount;
            Consumable *selectedConsumable;

            switch (choice) {
                case 1:
                    // Fight
                    listEnemies(enemies, nrOfEnemies);
                    choice = askForInt(1, nrOfEnemies);
                    fight(player, enemies[choice - 1]);
                    break;
                case 2:
                    // Use item
                    itemCount = listItems(player->inventory);
                    choice = askForInt(1, itemCount);
                    selectedConsumable = getItemAtPosition(choice, player->inventory);
                    selectedConsumable->use(player, selectedConsumable);
                    removeItem(player->inventory, selectedConsumable->id);
                    break;
                case 3:
                    // Escape
                    playerRoll = roll() + getModifier(player->dexterity);
                    if (playerRoll >= encounterDifficulty) {
                        printf("\nYou managed to escape from combat (%d).\n", playerRoll);
                        escaped = true;
                        setCanRest(player, true);
                    } else {
                        printf("\nYou failed to escape (%d).\n", playerRoll);
                    }
                    break;
                default:
                    perror("Unhandled switch case in combatEncounter!");
                    break;
            }

            bool enemiesAlive = false;
            for (int i = 0; i < nrOfEnemies; ++i) {
                if (enemies[i]->hp > 0)
                    enemiesAlive = true;
            }

            if (!enemiesAlive) {
                printf("\nYou have won!\n");
                hasWon = true;
            }

            playerTurn = false;
        }

        // Enemies' turn
        if (!hasWon && !escaped) {
            for (int i = 0; i < nrOfEnemies; ++i) {
                if (enemies[i]->hp <= 0)
                    continue;

                switch (enemies[i]->class) {
                    case WARRIOR:
                        enemyRoll = roll() + getModifier(enemies[i]->strength);
                        break;
                    case RANGER:
                        enemyRoll = roll() + getModifier(enemies[i]->dexterity);
                        break;
                    case MAGE:
                        enemyRoll = roll() + getModifier(enemies[i]->intelligence);
                        break;
                }

                if (enemyRoll > getArmorClass(player)) {
                    int damage = getDamage(enemies[i]);
                    player->hp -= damage;
                    printf("\n%s dealt %d damage to you (%d).\n", enemies[i]->name, damage, enemyRoll);
                } else {
                    printf("\n%s missed his attack (%d).\n", enemies[i]->name, enemyRoll);
                }
            }
            playerTurn = true;
        }
    }

    // In case of victory, the player gets the exp for the enemies
    // and for the encounter itself
    if (hasWon) {
        if (isBossBattle) {
            printf("\nAfter defeating the boss, you discover a shining rock that he was carrying");
            printf("\nKrystaltear collected!");
            player->nrOfKrystaltears++;
        }

        int expTotal = 0, goldTotal = 0;
        for (int i = 0; i < nrOfEnemies; ++i) {
            expTotal += enemies[i]->expAmount;
            goldTotal += enemies[i]->goldAmount;
        }
        expTotal += encounterExpAmount;
        earnGold(player, goldTotal);
        earnExp(player, expTotal);
        setCanRest(player, true);

        printf("\n%s has earned %d exp.", player->name, expTotal);
        printf("\n%s has earned %d gold.", player->name, goldTotal);
    }

    // Frees the loot table of the enemies, then the enemies pointer itself
    for (int i = 0; i < nrOfEnemies; ++i) {
        free(enemies[i]->lootTable);
        free(enemies[i]);
    }
    free(enemies);
}

void listEnemies(Enemy **enemies, int nrOfEnemies) {
    for (int i = 0; i < nrOfEnemies; ++i) {
        Enemy *e = enemies[i];
        if (e->hp > 0) {
            printf("\n[%d] %s (lvl %d), HP: %d / %d", i + 1, e->name, e->level, e->hp, e->maxHp);
        }
    }
}

void fight(Character *player, Enemy *enemy) {
    int enemyArmorClass = enemy->armor;
    int playerRoll = roll();
    int modifiedRoll;
    switch (player->class) {
        case WARRIOR:
            modifiedRoll = playerRoll + getModifier(player->strength);
            break;
        case RANGER:
            modifiedRoll = playerRoll + getModifier(player->dexterity);
            break;
        case MAGE:
            modifiedRoll = playerRoll + getModifier(player->intelligence);
            break;
    }

    if (playerRoll == 20) {
        // Crit
        int critDamage = getPlayerDamage(player) * 2;
        enemy->hp -= critDamage;
        printf("\nYou hit(%d) %s critically, and dealt %d damage.", playerRoll, enemy->name, critDamage);
    } else if (playerRoll == 1) {
        // Crit miss
        printf("\nYour attack critically missed(%d) %s.", playerRoll, enemy->name);
    } else if (modifiedRoll > enemyArmorClass) {
        int damage = getPlayerDamage(player);
        enemy->hp -= damage;
        printf("\nYou hit(%d) %s, and dealt %d damage.", playerRoll, enemy->name, damage);
    } else {
        printf("\nYour attack missed(%d) %s.", playerRoll, enemy->name);
    }

    if (enemy->hp <= 0) {
        printf("\n%s has died.", enemy->name);
        for (int i = 0; i < enemy->lootCount; ++i) {
            printf("\n%s acquired from %s.", getItemName(enemy->lootTable[i]), enemy->name);
            addItem(player->inventory, enemy->lootTable[i]);
        }
    }
}

void merchantEncounter(Character *player) {
    printf("\nYou find a merchant along the road");
    printf("\n[1]: Look at the merchant's wares");
    printf("\n[2]: Continue your adventures");

    Inventory *merchantInv = initInventory();
    // The total number of the merchant's items
    int itemCount = player->level / 3 + 2;
    enum itemID randomItem;
    for (int i = 1; i <= itemCount; ++i) {
        // If the player is past level 3, this enables the
        // generation of the enchanced items
        if (player->level > 3) {
            randomItem = rand() % 6;
        } else {
            randomItem = rand() % 3;
        }
        addItem(merchantInv, randomItem);
    }

    while (askForInt(1, 2) == 1) {
        itemCount = listMerchantItems(merchantInv);
        int choice = askForInt(1, itemCount);
        Consumable *selectedItem = getItemAtPosition(choice, merchantInv);
        if (player->gold < getItemPrice(selectedItem->id)) {
            int goldNeeded = getItemPrice(selectedItem->id) - player->gold;
            printf("\nYou don't have enought gold for a %s. You need %d more coins.", selectedItem->name, goldNeeded);
        } else {
            removeItem(merchantInv, selectedItem->id);
            addItem(player->inventory, selectedItem->id);
            player->gold -= getItemPrice(selectedItem->id);
            printf("\nYou successfully bought a %s", selectedItem->name);
            printf("\nRemaining gold: %d", player->gold);
        }

        printf("\n");
        printf("\n[1]: Continue shopping");
        printf("\n[2]: Leave the merchant's stall");
    }

    freeInventoryFromMemory(merchantInv);
}

void smithEncounter(Character *player) {
    printf("\nAs you walk the bustling streets of Herton, you notice the pleasant hammering "
           "of the local smithy and the sound of metal hitting metal. "
           "Maybe it's time to replace your gear with a better one, you think, when taking a glance"
           " at your worn-out equipment.");
    printf("\n[1]: Upgrade your gear (Krystaltear needed)");
    printf("\n[2]: Continue your adventures without upgrading your gear");
    int choice = askForInt(1, 2);

    if (choice == 1) {
        for (int i = 0; i < 4; ++i) {
            printf("\n[%d] %s --> %s", i + 1, player->armors[i].name,
                   getNextLevelArmor(player->armors[i].type, player->armors[i].value).name);
        }
        choice = askForInt(1, 4);
        if (player->nrOfKrystaltears < 1) {
            printf("\nUnfortunately, you don't have any Krystaltear. Continue your adventures"
                   " to collect this rare ore.");
        } else {
            player->armors[choice - 1] = getNextLevelArmor(choice - 1, player->armors[choice - 1].value);
            player->nrOfKrystaltears--;
        }
    } else {
        printf("\nYou decide today is not the day you part with your beloved gear, either by the "
               "lack of Krystaltear or gold in your purse.");
    }
}






