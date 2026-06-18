#ifndef EQUIPMENT_H
#define EQUIPMENT_H

typedef struct {
    char name[50];
    char id[15];
    double costPerHour;
    double powerRating;
    int remainingEquipment;
    int status;
} Equipment;

#endif