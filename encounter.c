#include "encounter.h"
#include "debugmalloc.h"


void combatEncounter(Character *player, int nrOfEnemies) {
    Enemy **enemies = malloc(nrOfEnemies * sizeof(Enemy));
    int encounterLevel = player->level;
    int encounterExpAmount = encounterLevel * 100;

    for (int i = 0; i < nrOfEnemies; ++i) {
        enemies[i] = generateEnemy(encounterLevel, WARRIOR, "");
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

            switch (choice) {
                case 1:
                    // Fight
                    listEnemies(enemies, nrOfEnemies);
                    choice = askForInt(1, nrOfEnemies);
                    fight(player, enemies[choice - 1]);
                    break;
                case 2:
                    // Use item
                    break;
                case 3:
                    // Escape
                    playerRoll = roll() + getModifier(player->dexterity);
                    if (playerRoll >= encounterDifficulty) {
                        printf("\nYou managed to escape from combat (%d).\n", playerRoll);
                        escaped = true;
                        setCanRest(player, true);
                    }
                    else {
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
        for (int i = 0; i < nrOfEnemies; ++i) {
            getExp(player, enemies[i]->expAmount);
        }

        getExp(player, encounterExpAmount);
        setCanRest(player, true);
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
    }
    else if (playerRoll == 1) {
        // Crit miss
        printf("\nYour attack critically missed(%d) %s.", playerRoll, enemy->name);
    }
    else if (modifiedRoll > enemyArmorClass) {
        int damage = getPlayerDamage(player);
        enemy->hp -= damage;
        printf("\nYou hit(%d) %s, and dealt %d damage.", playerRoll, enemy->name, damage);
    }
    else {
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

int roll() {
    return rand() % 20 + 1;
}




