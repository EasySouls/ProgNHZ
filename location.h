#ifndef PROGNZH_THSTAM_LOCATION_H
#define PROGNZH_THSTAM_LOCATION_H

typedef struct locationStruct {
    char name[50];
    char description[150];

} Location;

typedef struct locationNodeStruct {
    Location *current;
    struct locationNodeStruct *next;
} LocationNode;

#endif //PROGNZH_THSTAM_LOCATION_H
