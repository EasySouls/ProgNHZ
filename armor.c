#include "armor.h"
#include "debugmalloc.h"

Armor getNextLevelArmor(enum armorType type, int value) {
    Armor result;
    result.type = type;
    result.value = value + 1;

    if (type == HEAD) {
        switch (value) {
            case 0:
                return (Armor){type, value + 1, "Leather Helm"};
            case 1:
                return (Armor){type, value + 1, "Iron Helmet"};
            case 2:
                return (Armor){type, value + 1, "Steel Helmet"};
            default:
                return (Armor){type, value + 1, "EPIC HELMET"};
        }
    }
    else if (type == CHEST) {
        switch (value) {
            case 0:
                return (Armor){type, value + 1, "Leather Chestplate"};
            case 1:
                return (Armor){type, value + 1, "Chainmail"};
            case 2:
                return (Armor){type, value + 1, "Steel Breastplate"};
            default:
                return (Armor){type, value + 1, "EPIC CHESTPLATE"};
        }
    }
    else if (type == ARMS) {
        switch (value) {
            case 0:
                return (Armor){type, value + 1, "Leather Armguards"};
            case 1:
                return (Armor){type, value + 1, "Iron Armguards"};
            case 2:
                return (Armor){type, value + 1, "Steel Armguards"};
            default:
                return (Armor){type, value + 1, "EPIC HAND ARMOR"};
        }
    }
    else if (type == LEGS) {
        switch (value) {
            case 0:
                return (Armor){type, value + 1, "Leather Trousers"};
            case 1:
                return (Armor){type, value + 1, "Iron Greaves"};
            case 2:
                return (Armor){type, value + 1, "Steel Greaves"};
            default:
                return (Armor){type, value + 1, "EPIC LEG ARMOR"};
        }
    }

    return result;
}
