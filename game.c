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
//        character->inventory = malloc(sizeof(Inventory));
//        //character->armors = malloc(4 * sizeof(Armor));
//        character->armors[0] = (Armor){ HEAD, 0, "Empty"};
//        character->armors[1] = (Armor){ CHEST, 0, "Empty"};
//        character->armors[2] = (Armor){ ARMS, 0, "Empty"};
//        character->armors[3] = (Armor){ LEGS, 0, "Empty"};
    }
}

void mainMenu() {
    printf("\nMenu");
    printf("\n[1]: Travel");
    printf("\n[2]: Rest");
    printf("\n[3]: Level up");
    printf("\n[4]: Display stats");
    printf("\n[5]: Check inventory");
    printf("\n[6]: Save character");
    printf("\n[7]: Load character");
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
            break;
        case 5:
            displayInventory(character->inventory);
            break;
        case 6:
            saveCharacter(character);
            break;
        case 7:
            loadCharacter();
            break;
        case 0:
            exitGame();
            break;
        default:
            fprintf(stderr, "Unhandled input in game::mainMenu");
            break;
    }
}

void travel() {
    combatEncounter(character, 2);
}

void rest() {

}

void levelUp() {

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
        fprintf(outfile, "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;",
                c->name, c->level, c->exp, c->distanceTraveled, c->gold, c->hp, c->mana,
                c->class, c->strength, c->dexterity, c->constitution, c->intelligence, c->wisdom, c->charisma);
        // Saving the armors
        for (int i = 0; i < 4; ++i) {
            fprintf(outfile, "%d;%d;%s;",
                    character->armors[i].type, character->armors[i].value, character->armors[i].name);
        }
        fprintf(outfile, "\n");
        printf("\n%s saved successfully!\n", character->name);
    }

    fclose(outfile);

}

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

        CharacterBase *base = malloc(sizeof(CharacterBase));

        rewind(infile);

        char name[50];
        char c;
        int index = 0;
        c = (char)fgetc(infile);
        while (c != ';') {
            name[index] = c;
            c = (char)fgetc(infile);
            index++;
        }

        strcpy(base->name, name);

        fscanf(infile, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;", &base->level, &base->exp, &base->distanceTraveled, &base->gold, &base->hp,
               &base->mana, &base->class, &base->strength, &base->dexterity, &base->constitution, &base->intelligence, &base->wisdom, &base->charisma);
        // Reading the armors' data
        for (int i = 0; i < 4; ++i) {
            fscanf(infile, "%d;%d;", &base->armors[i].type, &base->armors[i].value);
            char armorName[50];
            int idx = 0;
            c = (char)fgetc(infile);
            while (c != ';') {
                name[idx] = c;
                c = (char)fgetc(infile);
                idx++;
            }
            strcpy(base->armors[i].name, armorName);
        }
        fclose(infile);

        character = calcStats(base);

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
    printf("\n>>");
    scanf("%49s", name);

    // Class selection
    Class class;
    int choice;

    printf("\nSelect your class: ");
    printf("\n[1]: WARRIOR");
    printf("\n -- warrior desc --");
    printf("\n[2]: RANGER");
    printf("\n -- ranger desc --");
    printf("\n[3]: MAGE");
    printf("\n -- mage desc --");
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











