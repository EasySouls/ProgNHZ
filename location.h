#ifndef PROGNZH_THSTAM_LOCATION_H
#define PROGNZH_THSTAM_LOCATION_H

enum Locations {
    VILLAGE,
    TOWN,
    FOREST
};

typedef struct locationStruct {
    char name[50];
    char description[150];

} Location;

typedef struct locationNodeStruct {
    Location *current;
    struct locationNodeStruct *next;
} LocationNode;

#endif //PROGNZH_THSTAM_LOCATION_H
