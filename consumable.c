#include "consumable.h"
#include "character.h"

#include "debugmalloc.h"

 int consumablePrices[6]  = { 200, 150, 300, 500, 400, 650};

void restoreHp(struct playerStructure *target, Consumable *self) {
    target->hp += self->health;
    if (target->hp > target->maxHp)
        target->hp = target->maxHp;
    printf("\n%d health points restored", self->health);
}

void restoreMana(struct playerStructure *target, Consumable *self) {
    target->mana += self->mana;
    if (target->mana > target->maxMana)
        target->mana = target->maxMana;
    printf("\n%d mana points restored", self->mana);
}

void addDamage(struct playerStructure *target, Consumable *self) {
    target->damageMin += self->damage;
    target->damageMax += self->damage;
    printf("\n%d temporary damage added", self->damage);
}

