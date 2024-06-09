#include "statement.h"
#include "deposit.h"
double amount;
void depositMoney() {

    char toContinue;
    char confirmProceed;

    printf(ANSI_BOLD ANSI_ITALIC);
    printf("Enter the amount to deposit: $");
    scanf("%lf", &amount);
    printf(ANSI_RESET);


    if (!checkStatementFile()) {
        checkStatementFile();
    }

    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid deposit amount! Please enter a valid amount.\n\n" ANSI_RESET);
        depositMoney();
    }

    // Showing confirmation for deposit...
    clearInputBuffer();
    printf(ANSI_BOLD ANSI_ITALIC);
    printf("\nAre you sure you want to deposit $%.2f? (Enter Y to confirm or press any key for main menu): ", amount);
    scanf("%c", &confirmProceed);
    printf(ANSI_RESET);
    printf("\n");

    if (confirmProceed != 'Y' && confirmProceed != 'y') {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "Your deposit transection has been cancelled!\n\n" ANSI_RESET);
        showDashboardMenu();
    }
    
    currentBalance += amount; // currentBalance = currentBalance + amount
    saveBalanceToFile();
    addNewTransactionRecord(amount, currentUsername, currentUserRole, "Deposit");

    printf("\n");
    printf(ANSI_BOLD);
    system("cls");
    printf(ANSI_GREEN "Successfully deposited the amount of " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
    printf(ANSI_RESET);
    printf("\n\n");
    printf(ANSI_BOLD);
    printf(ANSI_GREEN "New account balance is " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
    printf(ANSI_RESET);
    printf("\n\n");
    usleep(500000);

    // If user want to make another deposit...
    clearInputBuffer();
    printf(ANSI_BOLD ANSI_ITALIC);
    printf("If you want to make another deposit, Enter Y or press any key to go for main menu: ");
    scanf("%c", &toContinue);
    printf(ANSI_RESET);
    printf("\n");

    if (toContinue == 'Y' || toContinue == 'y') {
        depositMoney();
    } else {
        system("cls");
        showDashboardMenu();
    }
}
