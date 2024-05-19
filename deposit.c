#include <stdio.h>


extern double currentBalance;
extern void saveBalanceToFile();

void depositMoney(double amount) {
    
    currentBalance += amount;
    saveBalanceToFile();
    addNewTransactionRecord(amount, currentUsername, currentUserRole, "Deposit");

    printf("\n");
    printf(ANSI_BOLD);
    printf(ANSI_GREEN "Successfully deposited the amount of " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
    printf(ANSI_RESET);
    printf("\n\n");
    printf(ANSI_BOLD);
    printf(ANSI_GREEN "New account balance is balance is " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
    printf(ANSI_RESET);
    printf("\n\n");
    usleep(500000);
}
