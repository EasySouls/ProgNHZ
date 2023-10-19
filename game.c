#include <stdlib.h>
#include "game.h"
#include "debugmalloc.h"

const char filename[] = "characters.txt";

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
    // separator();
    printf("\nMenu");
    printf("\n[1]: Travel");
    printf("\n[2]: Rest");
    printf("\n[3]: Level up");
    printf("\n[4]: Display stats");
    printf("\n[5]: Save character");
    printf("\n[6]: Load character");
    printf("\n[0]: Exit game");

    input = askForInt(0, 6);

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
            saveCharacter(character);
            break;
        case 6:
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
    FILE *outfile = fopen(filename, "a");

    if (outfile == NULL) {
        perror("Couldn't open characters.txt. The program will exit now.");
        exitGame();
    }

    if (character == NULL) {
        perror("The current character is null. ");
    } else {
        // Writing to the file
        fprintf(outfile, "%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                c->name, c->level, c->exp, c->distanceTraveled, c->gold, c->hp, c->mana,
                c->class, c->strength, c->dexterity, c->constitution, c->intelligence, c->wisdom, c->charisma);
        printf("\n%s saved successfully!\n", character->name);
    }

    fclose(outfile);

}

void loadCharacter() {
    FILE *infile = fopen(filename, "r");

    if (infile == NULL) {
        // Creates the file, since it didn't exist
        infile = fopen(filename, "w");
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

        CharacterBase base;

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

        strcpy(base.name, name);

        fscanf(infile, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", &base.level, &base.exp, &base.distanceTraveled, &base.gold, &base.hp,
               &base.mana, &base.class, &base.strength, &base.dexterity, &base.constitution, &base.intelligence, &base.wisdom, &base.charisma);
        fclose(infile);

        character = calcStats(&base);

        if (character == NULL) {
            printf("No previously saved characters found.");
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
    free(character);
    isRunning = false;
    quit = true;
}











