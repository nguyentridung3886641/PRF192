#include <stdio.h>
#include <string.h>
#include "Manager.h"

Equipment equipmentList[100];
int equipmentCount = 0;

Client clientList[100];
int clientCount = 0;

Rental rentalList[100];
int rentalCount = 0;


void inputEquipment(Equipment* self) {
    while (getchar() != '\n'); 

    printf("Enter Equipment ID: ");
    fgets(self->id, sizeof(self->id), stdin);
    self->id[strcspn(self->id, "\n")] = '\0';

    printf("Enter Equipment Name: ");
    fgets(self->name, sizeof(self->name), stdin);
    self->name[strcspn(self->name, "\n")] = '\0';
    
    printf("Enter Rental Cost: ");
    scanf("%lf", &self->cost);
    
    printf("Enter Power Rating: ");
    scanf("%lf", &self->powerRating);
}

int inputClient(Client* self) {

    printf("Enter Client ID: ");
    fgets(self->id, sizeof(self->id), stdin);
    self->id[strcspn(self->id, "\n")] = '\0';

    if (searchClientByID(self->id) != -1) {
        printf("Error: This Client ID already exists. Registration failed!\n");
        return 0;
    }

    printf("Enter Client Name: ");
    fgets(self->name, sizeof(self->name), stdin);
    self->name[strcspn(self->name, "\n")] = '\0';

    return 1;
}

int inputRental(Rental* self) {
    int clientIndex;
    int equipmentIndex;

    //Enter Rental ID - Exit if Rental ID not found
    printf("Enter Rental ID: ");
    fgets(self->rentalID, sizeof(self->rentalID), stdin);
    self->rentalID[strcspn(self->rentalID, "\n")] = '\0';

    if (searchRentalByID(self->rentalID) != -1) {
        printf("Error: Rental ID already exists! Order request failed.\n");
        return 0; 
    }

    //Enter Client ID - Exist if Client ID not found
    printf("Enter Client ID: ");
    fgets(self->clientID, sizeof(self->clientID), stdin);
    self->clientID[strcspn(self->clientID, "\n")] = '\0';

    clientIndex = searchClientByID(self->clientID);
    if (clientIndex == -1) {
        printf("Error: Client ID not found! Order request failed.\n");
        return 0; 
    }

    //Enter Equipment ID - Exist if Equipment ID not found
    printf("Enter Equipment ID: ");
    fgets(self->equipmentID, sizeof(self->equipmentID), stdin);
    self->equipmentID[strcspn(self->equipmentID, "\n")] = '\0';

    equipmentIndex = searchEquipmentByID(self->equipmentID);
    if (equipmentIndex == -1) {
        printf("Error: Equipment ID not found! Order request failed.\n");
        return 0; 
    }
    
    //Update Rental Cost
    self->equipmentCost = equipmentList[equipmentIndex].cost;

    //Enter Rental Time and Expected Return Time
    printf("Enter Start Time (hour): ");
    scanf("%d", &self->starTime);

    printf("Enter Expected Return Time (hour): ");
    scanf("%d", &self->expectedReturnTime);

    return 1;
}

void addEquipment() {
    Equipment object;
    inputEquipment(&object);
    int foundIDIndex = -1;
    int foundNameIndex = -1;
    //Check equipment's list if it already exist the device need to add
    for (int i = 0; i < equipmentCount; i++) {            
        if (strcmp(equipmentList[i].id, object.id) == 0)
            foundIDIndex = i;

        if (strcmp(equipmentList[i].name, object.name) == 0)
            foundNameIndex = i;

        if (foundIDIndex != -1 || foundNameIndex != -1)
            break;
    }
    //Increased number of device in list if it already exist
    if (foundIDIndex != -1 && foundNameIndex != -1) {
        equipmentList[foundIDIndex].remainingEquipment++;
        equipmentList[foundIDIndex].status = 0;
    }
    //Add new device if the device need to add dose not exist in list
    else if (foundIDIndex == -1 && foundNameIndex == -1) {
        equipmentList[equipmentCount] = object;
        equipmentList[equipmentCount].remainingEquipment = 1;
        equipmentList[equipmentCount].status = 0;
        equipmentCount++;
    }
    //Display an error message if the entered device information has a matching name but a different ID, or vice versa.
    else {
        printf("You may add an already exist equipment!");
    }
}

void addClient() {
    Client object;
    
    if (inputClient(&object) == 1) {
        clientList[clientCount] = object;
        clientCount++;
        printf("Client successfully added!\n");
    } else {
        printf("Failed to add client!\n");
    }
}

int searchEquipmentByID(char* id) {
    for (int i = 0; i < equipmentCount; i++) {
        if (strcmp(equipmentList[i].id, id) == 0)
            return i;
    }
    return -1;
}

void createRentalOrder() {
    Rental object;
    if (inputRental(&object) == 1) {
        
        rentalList[rentalCount] = object;
        equipmentList[searchEquipmentByID(object.equipmentID)].remainingEquipment--;
        rentalCount++;

        printf("Rental order successfully created!\n");
    }
    else
        printf("Rental order failed to create!\n");
}

//revenue statistics
void displayTotalRentalFees() {
    for ()
}