#include <stdlib.h>

#include "game.h"
#include "debugmalloc.h"

const char charactersFile[] = "characters.txt";

bool isRunning = false;
bool quit = false;
int input = 0;

Character *character = NULL;

void initGame() {
    isRunning = true;
    loadCharacter();

    if (character == NULL) {
        character = createCharacter();
    }
}

void mainMenu() {
    printf("\nMenu");
    printf("\n[1]: Travel");
    printf("\n[2]: Rest");
    printf("\n[3]: Level up");
    printf("\n[4]: Display stats");
    printf("\n[5]: Check inventory");
    printf("\n[6]: Equipped items");
    printf("\n[7]: Save and Load Submenu");
    printf("\n[0]: Exit game");

    input = askForInt(0, 7);

    switch (input) {
        case 1:
            travel();
            break;
        case 2:
            rest();
            break;
        case 3:
            levelUp();
            break;
        case 4:
            printStats();
            pressEnter();
            break;
        case 5:
            displayInventory(character->inventory);
            pressEnter();
            break;
        case 6:
            equippedItems(character);
            pressEnter();
            break;
        case 7:
            saveAndLoadSubmenu();
            break;
        case 0:
            exitGame();
            break;
        default:
            fprintf(stderr, "Unhandled input in game::mainMenu");
            break;
    }
}

void equippedItems(Character *player) {
    displayEquippedItems(player);
}

// Generates an encounter based on a random number, then checks whether the player is alive
// after the encounter
void travel() {
    int isBossBattle = character->distanceTraveled % 5 == 0 && character->distanceTraveled != 0;
    combatEncounter(character, 2, isBossBattle);

    if (character->hp <= 0) {
        printf("\nYou died. Better luck next time!");
        printf("\n -------- Press Enter to exit --------\n");
        fflush(stdin);
        while (getchar() != '\n')
            ;
        exitGame();
    }
    else {
        if (character->exp >= character->expToNext) {
            printf("\n%s can level up!\n", character->name);
        }
        character->distanceTraveled++;
        pressEnter();
    }
}

void rest() {
    if (character->canRest) {
        int restRoll = roll();
        if (restRoll == 20) {
            character->hp = character->maxHp;
            printf("\n%s has been healed to full hp.", character->name);
        }
        else if (restRoll == 1) {
            printf("\n%s slept really bad and couln't regain any hitpoints.", character->name);
        }
        else {
            character->hp += restRoll;
            if (character->hp > character->maxHp)
                character->hp = character->maxHp;

            printf("\n%s has recovered %d hitpoints.", character->name, restRoll);
        }
        setCanRest(character, false);
    }
    else {
        printf("\n%s cannot rest now. Adventure further to be able to rest.", character->name);
    }
}

void levelUp() {
    if (character->exp < character->expToNext) {
        int expNeeded = character->expToNext - character->exp;
        printf("\nNot enought exp to level up! %d more points needed.", expNeeded);
        return;
    }

    printf("\nChoose a stat to upgrade:");
    for (int i = 0; i < 6; ++i) {
        printf("\n[%d]: %s", i+1, getAttributeName(i));
    }

    input = askForInt(1, 6);
    character->exp -= character->expToNext;
    levelUpCharacter(character, input);
    updateStats(character);
}

// Prints the stats of the player to the standard output
void printStats() {
    displayStats(character);
}

void saveCharacter(Character *c) {
    FILE *outfile = fopen(charactersFile, "w");

    if (outfile == NULL) {
        perror("Couldn't open characters.txt. The program will exit now.");
        exitGame();
    }

    if (character == NULL) {
        perror("The current character is null. ");
    } else {
        // Writing to the file
        fprintf(outfile, "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;",
                c->name, c->level, c->exp, c->distanceTraveled, c->gold, c->hp, c->mana,
                c->class, c->strength, c->dexterity, c->constitution, c->intelligence, c->wisdom, c->charisma, c->canRest);
        // Saving the armors
        for (int i = 0; i < 4; ++i) {
            fprintf(outfile, "%d;%d;%s;",
                    character->armors[i].type, character->armors[i].value, character->armors[i].name);
        }
        fprintf(outfile,"\n");
        // Saving the inventory
        Inventory *inv = character->inventory;
        while (inv != NULL) {
            Consumable *current = inv->current;
            fprintf(outfile, "%d;", current->id);
            inv = inv->next;
        }
        fprintf(outfile, "\n");
        printf("\n%s saved successfully!\n", character->name);
    }

    fclose(outfile);

}

/*
 * Loads a character from the file containing the characters
 * If the file doesn't exist, creates it
 * If the file does exist, it checks whether it is empty. If empty, or the file is nonexistent,
 * it returns, otherwise reads the character into a CharacterBase struct. Then calls the initLoadedCharacter function,
 * which then sets the character variable
*/
void loadCharacter() {
    FILE *infile = fopen(charactersFile, "r");

    if (infile == NULL) {
        // Creates the file, since it didn't exist
        infile = fopen(charactersFile, "w");
        fclose(infile);
        printf("No previously saved characters found.");
    }
    else {
        fseek(infile, 0, SEEK_END);
        int filesize = ftell(infile);
        if (filesize == 0) {
            printf("No previously saved characters found.");
            return;
        }
        rewind(infile);

        CharacterBase *base = malloc(sizeof(CharacterBase));

        char name[50];
        fscanf(infile, "%[^;];", name);
        strcpy(base->name, name);

        fscanf(infile, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;", &base->level, &base->exp, &base->distanceTraveled, &base->gold, &base->hp,
               &base->mana, &base->class, &base->strength, &base->dexterity, &base->constitution, &base->intelligence, &base->wisdom, &base->charisma, &base->canRest);
        // Reading the armors' data
        for (int i = 0; i < 4; ++i) {
            fscanf(infile, "%d;%d;", &base->armors[i].type, &base->armors[i].value);
            char armorName[50];
            fscanf(infile, "%[^;];", armorName);
            strcpy(base->armors[i].name, armorName);
        }
        fscanf(infile, "\n");

        character = initLoadedCharacter(base);

        // Reading the items' data
        itemID tempId;
        while (fscanf(infile, "%d;", &tempId) == 1) {
            addItem(character->inventory, tempId);
        }

        fclose(infile);
        free(base);

        if (character == NULL) {
            perror("Cannot load character properly");
        } else {
            printf("\n%s loaded successfully!\n", character->name);
        }
    }
}

Character *createCharacter() {

    char name[50];

    printf("\nWhat will be the name of your character?");
    printf("\n(max 49 characters)");
    printf("\n>>");
    fflush(stdin);
    scanf("%[^\n]", name);

    // Class selection
    Class class;
    int choice;

    printf("\nSelect your class: ");
    printf("\n[1]: WARRIOR");
    printf("\nDescription:\n"
           "For some, their rage springs from a communion with fierce animal spirits. "
           "Others draw from a roiling reservoir of anger at a world full of pain. "
           "For every barbarian, rage is a power that fuels not just a battle frenzy but also uncanny reflexes,"
           " resilience, and feats of strength.");
    printf("\nStats:\n"
           "Strength: 16, Dexterity: 12, Constitution: 15, Intelligence: 8, Wisdom: 8, Charisma: 13\n");
    printf("\n[2]: RANGER");
    printf("\nDescription:\n"
           "Far from the bustle of cities and towns, past the hedges that shelter the most "
           "distant farms from the terrors of the wild, amid the dense-packed trees of trackless "
           "forests and across wide and empty plains, rangers keep their unending watch.\n");
    printf("\nStats:\n"
           "Strength: 14, Dexterity: 18, Constitution: 12, Intelligence: 10, Wisdom: 13, Charisma: 12\n");
    printf("\n[3]: MAGE");
    printf("\nDescription:\nWizards’ lives are seldom mundane. The closest a wizard is likely to "
           "come to an ordinary life is working as a sage or lecturer in a library or university, "
           "teaching others the secrets of the multiverse. Other wizards sell their services as diviners, "
           "serve in military forces, or pursue lives of crime or domination.\n");
    printf("\nStats:\n"
           "Strength: 8, Dexterity: 11, Constitution: 8, Intelligence: 17, Wisdom: 15, Charisma: 14\n");
    choice = askForInt(1, 3);

    switch (choice) {
        case 1:
            class = WARRIOR;
            break;
        case 2:
            class = RANGER;
            break;
        case 3:
            class = MAGE;
            break;
        default:
            class = WARRIOR;
            fprintf(stderr, "Unhandled case in switch statement in game::createCharacter");
    }

    // Creating a new character struct which has their values set based upon the given attributes
    return newCharacter(name, class);
}

void saveAndLoadSubmenu() {
    printf("\nSave and Load Submenu\n");
    printf("[1]: Save current character\n");
    printf("[2]: Load saved character\n");
    printf("[3]: Create a new character\n");
    printf("[4]: Exit from submenu\n");
    input = askForInt(1, 4);

    switch (input) {
        case 1:
            saveCharacter(character);
            break;
        case 2:
            loadCharacter();
            break;
        case 3:
            freeInventoryFromMemory(character->inventory);
            free(character);
            character = createCharacter();
            break;
        case 4:
        default:
            break;
    }
}

/* Exits the game
 * Sets isRunning to false, so the main function can stop calling the while loop
 * which basically runs the game
 * Also sets the quit variable to true, this way the game knows our character didn't die
 * but we chose to quit
 */
void exitGame() {
    freeInventoryFromMemory(character->inventory);
    free(character);
    isRunning = false;
    quit = true;
}











