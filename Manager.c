#include <stdio.h>
#include <string.h>
#include "Manager.h"

Equipment equipmentList[100];
int equipmentCount = 0;

Client clientList[100];
int clientCount = 0;

Rental rentalList[100];
int rentalCount = 0;

// ==========================================
// CÁC HÀM TÌM KIẾM BỔ TRỢ (UTILITY FUNCTIONS)
// ==========================================

int searchEquipmentByID(char* id) {
    for (int i = 0; i < equipmentCount; i++) {
        if (strcmp(equipmentList[i].id, id) == 0)
            return i;
    }
    return -1;
}

int searchClientByID(char* id) {
    for (int i = 0; i < clientCount; i++) {
        if (strcmp(clientList[i].id, id) == 0)
            return i;
    }
    return -1;
}

int searchRentalByID(char* id) {
    for (int i = 0; i < rentalCount; i++) {
        if (strcmp(rentalList[i].rentalID, id) == 0)
            return i;
    }
    return -1;
}


// ==========================================
//          CÁC HÀM NHẬP DỮ LIỆU
// ==========================================

void inputEquipment(Equipment* self) {
    while (getchar() != '\n'); 

    printf("Enter Equipment ID: ");
    fgets(self->id, sizeof(self->id), stdin);
    self->id[strcspn(self->id, "\n")] = '\0';

    printf("Enter Equipment Name: ");
    fgets(self->name, sizeof(self->name), stdin);
    self->name[strcspn(self->name, "\n")] = '\0';
    
    printf("Enter Rental Cost: ");
    scanf("%lf", &self->costPerHour);
    
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

    printf("Enter Rental ID: ");
    fgets(self->rentalID, sizeof(self->rentalID), stdin);
    self->rentalID[strcspn(self->rentalID, "\n")] = '\0';

    if (searchRentalByID(self->rentalID) != -1) {
        printf("Error: Rental ID already exists! Order request failed.\n");
        return 0; 
    }

    printf("Enter Client ID: ");
    fgets(self->clientID, sizeof(self->clientID), stdin);
    self->clientID[strcspn(self->clientID, "\n")] = '\0';

    clientIndex = searchClientByID(self->clientID);
    if (clientIndex == -1) {
        printf("Error: Client ID not found! Order request failed.\n");
        return 0; 
    }

    printf("Enter Equipment ID: ");
    fgets(self->equipmentID, sizeof(self->equipmentID), stdin);
    self->equipmentID[strcspn(self->equipmentID, "\n")] = '\0';

    equipmentIndex = searchEquipmentByID(self->equipmentID);
    if (equipmentIndex == -1) {
        printf("Error: Equipment ID not found! Order request failed.\n");
        return 0; 
    }
    
    if (equipmentList[equipmentIndex].remainingEquipment <= 0) {
        printf("Error: This equipment is out of stock!\n");
        return 0;
    }
    
    self->equipmentCost = equipmentList[equipmentIndex].costPerHour;

    printf("Enter Start Time (Hour): ");
    scanf("%d", &self->starTime);

    printf("Enter Expected Return Time (Hour): ");
    scanf("%d", &self->expectedReturnTime);

    self->totalCostExpected = self->equipmentCost * (self->expectedReturnTime - self->starTime);
    printf("Amount to be paid upfront: %.2lf\n", self->totalCostExpected);

    while (getchar() != '\n'); // Clean buffer

    return 1;
}


// ==========================================
//             CÁC HÀM NGHIỆP VỤ
// ==========================================

void addEquipment() {
    Equipment object;
    inputEquipment(&object);
    int foundIDIndex = -1;
    int foundNameIndex = -1;
    
    for (int i = 0; i < equipmentCount; i++) {            
        if (strcmp(equipmentList[i].id, object.id) == 0)
            foundIDIndex = i;

        if (strcmp(equipmentList[i].name, object.name) == 0)
            foundNameIndex = i;
    }
    
    if (foundIDIndex != -1 && foundIDIndex == foundNameIndex) {
        equipmentList[foundIDIndex].remainingEquipment++;
        printf("Equipment exist. Increased stock quantity!\n");
    }
    else if (foundIDIndex == -1 && foundNameIndex == -1) {
        equipmentList[equipmentCount] = object;
        equipmentList[equipmentCount].remainingEquipment = 1;
        equipmentList[equipmentCount].status = 0;
        equipmentCount++;
        printf("New equipment added successfully!\n");
    }
    else {
        printf("Error: Data mismatch! You may have entered a wrong ID or Name.\n");
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

void createRentalOrder() {
    Rental object;
    if (inputRental(&object) == 1) {
        rentalList[rentalCount] = object;
        equipmentList[searchEquipmentByID(object.equipmentID)].remainingEquipment--;
        rentalCount++;
        printf("Rental order successfully created!\n");
    }
    else {
        printf("Rental order failed to create!\n");
    }
}

void calculateTotalFees(Rental* rental, int actualReturnTime) {
    double baseRentalFee = (rental->expectedReturnTime - rental->starTime) * rental->equipmentCost;
    
    double penaltyFee = 0;
    if (actualReturnTime > rental->expectedReturnTime) {
        int lateTime = actualReturnTime - rental->expectedReturnTime;
        penaltyFee = lateTime * rental->equipmentCost * 1.5;
    }
    
    rental->actualReturnTime = actualReturnTime;
    rental->totalCost = baseRentalFee + penaltyFee;
}

void returnEquipment() {
    char rentalID[15];

    printf("Enter Rental ID to return: ");
    fgets(rentalID, sizeof(rentalID), stdin);
    rentalID[strcspn(rentalID, "\n")] = '\0';

    int rentalIndex = searchRentalByID(rentalID);
    if (rentalIndex == -1) {
        printf("Error: Rental ID not found!\n");
        return;
    }

    int actualTime;
    printf("Enter Actually Return Time (Hour): ");
    scanf("%d", &actualTime);
    while (getchar() != '\n');

    calculateTotalFees(&rentalList[rentalIndex], actualTime);

    int eqIndex = searchEquipmentByID(rentalList[rentalIndex].equipmentID);
    if (eqIndex != -1) {
        equipmentList[eqIndex].remainingEquipment++;
    }

    printf("Equipment returned successfully!\n");
    printf("Total Cost to pay: %.2lf\n", rentalList[rentalIndex].totalCost);
}

void displayTotalRentalFees() {
    double totalRentalFees = 0;
    for (int i = 0; i < rentalCount; i++) {
        totalRentalFees += rentalList[i].totalCost;
    }
    printf("Total revenue is: %.2lf\n", totalRentalFees);
}


// ==========================================
//       PHÂN NHÓM, SẮP XẾP & LƯU FILE
// ==========================================

void groupEquipmentByStatus() {
    printf("\n--- AVAILABLE EQUIPMENT ---\n");
    for (int i = 0; i < equipmentCount; i++) {
        if (equipmentList[i].remainingEquipment > 0) {
            printf("ID: %s | Name: %s | Qty: %d | Cost: %.2lf\n", 
                   equipmentList[i].id, equipmentList[i].name, equipmentList[i].remainingEquipment, equipmentList[i].costPerHour);
        }
    }

    printf("\n--- RENTED EQUIPMENT ---\n");
    for (int i = 0; i < equipmentCount; i++) {
        if (equipmentList[i].remainingEquipment == 0) {
            printf("ID: %s | Name: %s | Qty: %d | Cost: %.2lf\n", 
                   equipmentList[i].id, equipmentList[i].name, equipmentList[i].remainingEquipment, equipmentList[i].costPerHour);
        }
    }
}

void sortRentalsByDuration() {
    for (int i = 0; i < rentalCount - 1; i++) {
        for (int j = i + 1; j < rentalCount; j++) {
            int durationI = rentalList[i].expectedReturnTime - rentalList[i].starTime;
            int durationJ = rentalList[j].expectedReturnTime - rentalList[j].starTime;
            
            if (durationJ > durationI) {
                Rental temp = rentalList[i];
                rentalList[i] = rentalList[j];
                rentalList[j] = temp;
            }
        }
    }
    printf("Rentals sorted by duration successfully!\n");
}

void sortRentalsByClientName() {
    for (int i = 0; i < rentalCount - 1; i++) {
        for (int j = i + 1; j < rentalCount; j++) {

            int clientIdxI = searchClientByID(rentalList[i].clientID);
            int clientIdxJ = searchClientByID(rentalList[j].clientID);
            
            if (clientIdxI != -1 && clientIdxJ != -1) {

                if (strcmp(clientList[clientIdxI].name, clientList[clientIdxJ].name) > 0) {
                    Rental temp = rentalList[i];
                    rentalList[i] = rentalList[j];
                    rentalList[j] = temp;
                }
            }
        }
    }
    printf("Rentals sorted by Client Name successfully!\n");
}

void saveDataToFile() {
    FILE* file = fopen("RentalSystemData.txt", "w");
    if (file == NULL) {
        printf("Error: Cannot create or open file for saving!\n");
        return;
    }

    fprintf(file, "=== EQUIPMENT DATA (%d items) ===\n", equipmentCount);
    for (int i = 0; i < equipmentCount; i++) {
        fprintf(file, "%s|%s|%.2lf|%d\n", 
                equipmentList[i].id, equipmentList[i].name, equipmentList[i].costPerHour, equipmentList[i].remainingEquipment);
    }

    fprintf(file, "\n=== CLIENT DATA (%d clients) ===\n", clientCount);
    for (int i = 0; i < clientCount; i++) {
        fprintf(file, "%s|%s\n", clientList[i].id, clientList[i].name);
    }

    fprintf(file, "\n=== RENTAL ORDER DATA (%d orders) ===\n", rentalCount);
    for (int i = 0; i < rentalCount; i++) {
        fprintf(file, "%s|Client:%s|Equip:%s|Start:%d|Expected:%d|Actual:%d|TotalCost:%.2lf\n", 
                rentalList[i].rentalID, rentalList[i].clientID, rentalList[i].equipmentID, 
                rentalList[i].starTime, rentalList[i].expectedReturnTime, 
                rentalList[i].actualReturnTime, rentalList[i].totalCost);
    }

    fclose(file);
    printf("All system data has been successfully saved to 'RentalSystemData.txt'!\n");
}