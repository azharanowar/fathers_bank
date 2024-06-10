#include "bill_payments.h"

void billPayments() {
    printf(ANSI_BG_WHITE ANSI_BOLD "\t **** CHOOSE MENU FROM BELOW **** " ANSI_RESET); 
    printf("\n\n");

    printf(ANSI_BOLD);
    printf(" 1. Pay Electricity Bill\n");
    printf(" 2. Pay Gas Bill\n");
    printf(" 3. Pay Transportation Bill\n");
    printf(" 0. Exit\n");
    printf(ANSI_RESET);

    printf(ANSI_BOLD ANSI_CYAN ANSI_ITALIC);
    printf("\nEnter your choice: ");
    int choice;
    scanf("%d", &choice);
    printf(ANSI_RESET);
    printf("\n");

    switch (choice) {
        case 1:
            system("cls");
            payElectricityBill();
            return;
        case 2:
            system("cls");
            payGasBill();
            return;
        case 3:
            system("cls");
            payTransportationBill();
            return;
        case 0:
            system("cls");
            return;
        default:
            system("cls");
            printf(ANSI_RED ANSI_ITALIC "Wrong menu choice! Please enter 1-3 or 0 to exit.\n\n" ANSI_RESET);
            showDashboardMenu();
            break;
    }
}

void payElectricityBill() {
    printf(ANSI_BOLD "Enter the amount to pay for the electricity bill: $");
    double amount;
    scanf("%lf", &amount);
    printf(ANSI_RESET);

    // Here will be some function with intregation with other system to pay actual bill in the backend with API
    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid bill amount! Please enter a valid amount to pay.\n\n" ANSI_RESET);
        return;
    }

    if (currentBalance < amount) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInsufficient balance for paying bill of the amount $%.2f.\n\n" ANSI_RESET, amount);
        return;
    } else {
        
        // Print withdrawal confirmation
        printf("\n");
        system("cls");
        printf(ANSI_BOLD);
        loadingAnimation("Electricity bill payment is under processing, please wait", 500000);
        printf(ANSI_GREEN "Electricity bill payment successfull with the amount of " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
        printf(ANSI_RESET);

        printf("\n\n");

        currentBalance -= amount; // currentBalance = currentBalance - amount;
        saveBalanceToFile();

        printf(ANSI_BOLD);
        printf(ANSI_GREEN "New account balance is balance is " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
        printf(ANSI_RESET);
        printf("\n\n");
        usleep(500000);

        // Generate withdraw statement
        addNewTransactionRecord(amount, currentUsername, currentUserRole, "ElecBillPayment");
    }
}

void payGasBill() {
    printf(ANSI_BOLD "Enter the amount to pay for the gas bill: $");
    double amount;
    scanf("%lf", &amount);
    printf(ANSI_RESET);

    // Here will be some function with intregation with other system to pay actual bill in the backend with API
    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid bill amount! Please enter a valid amount to pay.\n\n" ANSI_RESET);
        return;
    }

    if (currentBalance < amount) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInsufficient balance for paying bill of the amount $%.2f.\n\n" ANSI_RESET, amount);
        return;
    } else {
        // Print withdrawal confirmation
        printf("\n");
        system("cls");
        printf(ANSI_BOLD);
        loadingAnimation("Gas bill payment is under processing, please wait", 500000);
        printf(ANSI_GREEN "Gas bill payment successfull with the amount of " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
        printf(ANSI_RESET);

        printf("\n\n");

        currentBalance -= amount;
        saveBalanceToFile();

        printf(ANSI_BOLD);
        printf(ANSI_GREEN "New account balance is balance is " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
        printf(ANSI_RESET);
        printf("\n\n");
        usleep(500000);

        // Generate withdraw statement
        addNewTransactionRecord(amount, currentUsername, currentUserRole, "GasBillPayment");
    }
}

void payTransportationBill() {
    // Placeholder implementation for bill payment
    printf(ANSI_BOLD "Enter the amount to pay for the transportation bill: $");
    double amount;
    scanf("%lf", &amount);
    printf(ANSI_RESET);

    // Assuming here some processing to pay the bill, such as deducting the amount from the balance
    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid bill amount! Please enter a valid amount to pay.\n\n" ANSI_RESET);
        return;
    }

    if (currentBalance < amount) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInsufficient balance for paying bill of the amount $%.2f.\n\n" ANSI_RESET, amount);
        return;
    } else {
        // Print withdrawal confirmation
        printf("\n");
        system("cls");
        printf(ANSI_BOLD);
        loadingAnimation("Transportation bill payment is under processing, please wait", 500000);
        printf(ANSI_GREEN "Transportation bill payment successfull with the amount of " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
        printf(ANSI_RESET);

        printf("\n\n");

        currentBalance -= amount;
        saveBalanceToFile();
        

        printf(ANSI_BOLD);
        printf(ANSI_GREEN "New account balance is balance is " ANSI_RESET);
        printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
        printf(ANSI_RESET);
        printf("\n\n");
        usleep(500000);

        // Generate withdraw statement
        addNewTransactionRecord(amount, currentUsername, currentUserRole, "TransBillPayment");
    }
}