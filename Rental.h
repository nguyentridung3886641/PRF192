#ifndef RENTAL_H
#define RENTAL_H

typedef struct {
    char rentalID[15];
    char clientID[15];
    char equipmentID[15];
    int starTime;
    int expectedReturnTime;
    int actualReturnTime;
    double equipmentCost;
    double totalCost;
} Rental;

#endif