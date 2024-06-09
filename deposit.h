#ifndef DEPOSIT_H
#define DEPOSIT_H

extern double currentBalance;
extern char currentUsername[20]; 
extern char currentUserRole[20];

extern void saveBalanceToFile();
extern void addNewTransactionRecord(double amount, const char *username, const char *userRole, const char *transactionType);
extern void showDashboardMenu();

void depositMoney(); // Function to deposit money into the account

#endif // DEPOSIT_H
