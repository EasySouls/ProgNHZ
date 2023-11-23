#include "enemies.h"
#include "debugmalloc.h"

int getDamage(Enemy *enemy) {
    return rand() % (enemy->damageMax - enemy->damageMin + 1) + enemy->damageMin;
}

Enemy *generateEnemy(int level, Class class, char *name) {
    Enemy *enemy = malloc(sizeof(Enemy));
    switch (class) {
        case WARRIOR:
            if (strlen(name) > 0) {
                setEnemyName(enemy, name);
            } else {
                setEnemyName(enemy, "Warrior");
            }
            enemy->strength = 11 + level / 2;
            enemy->dexterity = 10;
            enemy->constitution = 10 + level / 3;
            enemy->intelligence = 8;
            enemy->wisdom = 9;
            enemy->charisma = 9 + level / 4;
            enemy->damageMin = 2 + getModifier(enemy->strength) * 2;
            enemy->damageMax = 2 + getModifier(enemy->strength) * 3;
            break;
        case RANGER:
            if (strlen(name) > 0) {
                setEnemyName(enemy, name);
            } else {
                setEnemyName(enemy, "Warrior");
            }
            enemy->strength = 12;
            enemy->dexterity = 12 + level / 2;
            enemy->constitution = 11;
            enemy->intelligence = 10;
            enemy->wisdom = 10 + level / 3;
            enemy->charisma = 12;
            enemy->damageMin = 2 + getModifier(enemy->dexterity) * 2;
            enemy->damageMax = 2 + getModifier(enemy->dexterity) * 3;
            break;
        case MAGE:
            if (strlen(name) > 0) {
                setEnemyName(enemy, name);
            } else {
                setEnemyName(enemy, "Warrior");
            }
            enemy->strength = 8;
            enemy->dexterity = 10;
            enemy->constitution = 8;
            enemy->intelligence = 12 + level / 3;
            enemy->wisdom = 11 + level / 3;
            enemy->charisma = 12;
            enemy->damageMin = 2 + getModifier(enemy->intelligence) * 2;
            enemy->damageMax = 2 + getModifier(enemy->intelligence) * 3;
            break;
    }

    enemy->level = 1;
    enemy->maxHp = (enemy->level * 20) + 5 * getModifier(enemy->constitution);

    int possibleMana = 5 + 3 * getModifier(enemy->intelligence) + 2 * getModifier(enemy->wisdom);
    if (possibleMana > 5) {
        enemy->maxMana = 5 + 3 * getModifier(enemy->intelligence) + 2 * getModifier(enemy->wisdom);
    } else {
        enemy->maxMana = 5;
    }

    enemy->hp = enemy->maxHp;
    enemy->mana = enemy->maxMana;
    enemy->armor = 8 + getModifier(enemy->dexterity);
    enemy->class = class;

    enemy->expAmount = enemy->level * 20;

    // TODO Generate loot randomly
    enemy->lootCount = 2;
    enemy->lootTable = malloc(enemy->lootCount * sizeof(itemID));
    enemy->lootTable[0] = HEALTH_POTION;
    enemy->lootTable[1] = MANA_POTION;

    return enemy;
}

void setEnemyName(Enemy *target, char *name) {
    strcpy(target->name, name);
}
