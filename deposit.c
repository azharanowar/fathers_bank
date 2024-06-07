#include "statement.h"

extern double currentBalance;
extern char currentUsername[20]; 
extern char currentUserRole[20];

extern void saveBalanceToFile();
extern void addNewTransactionRecord(double amount, const char *username, const char *userRole, const char *transactionType);

void depositMoney(double amount) {
    if (!checkStatementFile()) {
        checkStatementFile();
    }

    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid withdrawal amount! Please enter a valid amount.\n\n" ANSI_RESET);
        return;
    }
    
    currentBalance += amount;
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
}
