#ifndef MANAGER_H
#define MANAGER_H
#include "Equipment.h"
#include "Client.h"
#include "Rental.h"

void inputEquipment(Equipment* self);
int inputClient(Client* self);
int inputRental(Rental* self);
void addEquipment();
void addClient();
int searchEquipmentByID(char id[]);
void createRentalOrder();
double calculateLatePenalty(Rental rental, int actualReturnTime);
void displayTotalRentalFees();
void groupEquipmentByStatus();
void sortRentalsByDuration();
void sortRentalsByClientName();
void saveDataToFile();
void loadFromFile();

#endif