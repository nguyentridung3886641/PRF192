#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Manager.h"

void printDivider() {
    printf("\n======================================================================\n");
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void showMainMenu() {
    printDivider();
    printf("====== EQUIPMENT MANAGEMENT SYSTEM ======\n");
    printf("1. Search Management\n");
    printf("2. Core Business Operations\n");
    printf("3. Sort, Group & Storage\n");
    printf("0. Exit\n");
    printf("=========================================\n");
    printf("Select an option (0-3): ");
}

void showSubMenu1() {
    printDivider();
    printf("--- MENU: SEARCH MANAGEMENT ---\n");
    printf("1. Search Equipment by ID\n");
    printf("2. Search Client by ID\n");
    printf("3. Search Rental by ID\n");
    printf("0. Back to Main Menu\n");
    printf("-------------------------------\n");
    printf("Select an option (0-3): ");
}

void showSubMenu2() {
    printDivider();
    printf("--- MENU: CORE BUSINESS OPERATIONS ---\n");
    printf("1. Add Equipment\n");
    printf("2. Add Client\n");
    printf("3. Create Rental Order\n");
    printf("4. Display Total Rental Fees\n");
    printf("5. Return Equipment\n");
    printf("6. Calculate Late Penalty (Preview)\n");
    printf("0. Back to Main Menu\n");
    printf("--------------------------------------\n");
    printf("Select an option (0-6): ");
}

void showSubMenu3() {
    printDivider();
    printf("--- MENU: SORT, GROUP & Storage ---\n");
    printf("1. Group Equipment by Status\n");
    printf("2. Sort Rentals by Duration\n");
    printf("3. Sort Rentals by Client Name\n");
    printf("4. Save Data to File\n");
    printf("5. Load Data from File\n");
    printf("0. Back to Main Menu\n");
    printf("-----------------------------------\n");
    printf("Select an option (0-5): ");
}

void handleSubMenu1() {
    int choice;
    char idInput[50];
    int index; 
    do {
        showSubMenu1();
        scanf("%d", &choice);
        printDivider();
        
        switch(choice) {
            case 1:
                printf("Enter Equipment ID to search: ");
                scanf("%s", idInput);
                index = searchEquipmentByID(idInput);
                if (index != -1) {
                    printf("Found! Equipment is at index %d.\n", index);
                } else {
                    printf("Equipment ID '%s' not found.\n", idInput);
                }
                break;
            case 2:
                printf("Enter Client ID to search: ");
                scanf("%s", idInput);
                index = searchClientByID(idInput);
                if (index != -1) {
                    printf("Found! Client is at index %d.\n", index);
                } else {
                    printf("Client ID '%s' not found.\n", idInput);
                }
                break;
            case 3:
                printf("Enter Rental ID to search: ");
                scanf("%s", idInput);
                index = searchRentalByID(idInput);
                if (index != -1) {
                    printf("Found! Rental Order is at index %d.\n", index);
                } else {
                    printf("Rental ID '%s' not found.\n", idInput);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        if (choice != 0) {
            printDivider();
            pauseScreen();
        }
    } while(choice != 0);
}

extern Rental rentalList[100];

void handleSubMenu2() {
    int choice;
    int actualTime;
    char idInput[50];
    int rIndex;

    do {
        showSubMenu2();
        scanf("%d", &choice);
        printDivider();
        
        switch(choice) {
            case 1:
                addEquipment();
                break;
            case 2:
                addClient();
                break;
            case 3:
                createRentalOrder();
                break;
            case 4:
                displayTotalRentalFees();
                break;
            case 5:
                returnEquipment();
                break;
            case 6:
                printf("Enter Rental ID: ");
                scanf("%s", idInput);
                rIndex = searchRentalByID(idInput);
                if (rIndex == -1) {
                    printf("Error: Rental ID not found!\n");
                } else {
                    printf("Enter Expected Actual Return Time (Hour): ");
                    scanf("%d", &actualTime);
                    double costPreview = calculateTotalFees(&rentalList[rIndex], actualTime);
                    printf("Preview Total Cost (including penalties): %.2lf\n", costPreview);
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        if (choice != 0) {
            printDivider();
            pauseScreen();
        }
    } while(choice != 0);
}

void handleSubMenu3() {
    int choice;
    do {
        showSubMenu3();
        scanf("%d", &choice);
        printDivider();
        
        switch(choice) {
            case 1:
                groupEquipmentByStatus();
                break;
            case 2:
                sortRentalsByDuration();
                break;
            case 3:
                sortRentalsByClientName();
                break;
            case 4:
                saveDataToFile();
                break;
            case 5:
                loadFromFile();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        if (choice != 0) {
            printDivider();
            pauseScreen();
        }
    } while(choice != 0);
}

int main() {
    int mainChoice;
    do {
        showMainMenu();
        scanf("%d", &mainChoice);
        
        switch(mainChoice) {
            case 1:
                handleSubMenu1();
                break;
            case 2:
                handleSubMenu2();
                break;
            case 3:
                handleSubMenu3();
                break;
            case 0:
                printDivider();
                printf("Thank you for using the system. Goodbye!\n");
                printDivider();
                break;
            default:
                printDivider();
                printf("Invalid choice! Please select between 0 and 3.\n");
                pauseScreen();
        }
    } while(mainChoice != 0);
    
    return 0;
}
