#include "consumable.h"
#include "character.h"

void restoreHp(struct playerStructure *target, Consumable *self) {
    target->hp += self->health;
    if (target->hp > target->maxHp)
        target->hp = target->maxHp;
}

void restoreMana(struct playerStructure *target, Consumable *self) {
    target->mana += self->mana;
    if (target->mana > target->maxMana)
        target->mana = target->maxMana;
}