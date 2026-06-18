#ifndef MANAGER_H
#define MANAGER_H
#include "Equipment.h"
#include "Client.h"
#include "Rental.h"

int searchEquipmentByID(char* id);
int searchClientByID(char* id);
int searchRentalByID(char* id);

void inputEquipment(Equipment* self);
int inputClient(Client* self);
int inputRental(Rental* self);

void addEquipment();
void addClient();
void createRentalOrder();
void displayTotalRentalFees();
void returnEquipment();
double calculateLatePenalty(Rental rental, int actualReturnTime);

void groupEquipmentByStatus();
void sortRentalsByDuration();
void sortRentalsByClientName();
void saveDataToFile();
void loadFromFile();

#endif