// withdraw.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statement.c"

#define MAX_WITHDRAW_AMOUNT_DAILY 1000
#define MAX_WITHDRAW_AMOUNT_MONTHLY 5000
#define FATHER_ROLE "Father"
#define TRANSACTION_FILE "statement.txt"

extern double currentBalance;
extern char currentUsername[20];
extern char currentUserRole[20];

void readBalanceFromFile(); // Declare functions from account.c
void saveBalanceToFile();
double getCurrentBalance();

double totalWithdrawnDaily = 0;
double totalWithdrawnMonthly = 0;

int checkWithdrawalHistory(double amount);

int canWithdraw(double amount, const char *role) {
    // Check if the user can withdraw the specified amount
    if (strcmp(role, FATHER_ROLE) == 0) {
        return 1; // Father role can withdraw unlimited
    }

    // Check daily withdrawal limit
    if ((totalWithdrawnDaily + amount) > MAX_WITHDRAW_AMOUNT_DAILY) {
        printf("Daily withdrawal limit exceeded\n");
        return 0;
    }

    // Check monthly withdrawal limit
    if ((totalWithdrawnMonthly + amount) > MAX_WITHDRAW_AMOUNT_MONTHLY) {
        printf("Monthly withdrawal limit exceeded\n");
        return 0;
    }

    // Check user's historical withdrawals
    if (!checkWithdrawalHistory(amount)) {
        printf("Monthly withdrawal limit exceeded based on historical withdrawals\n");
        return 0;
    }

    return 1;
}

void updateWithdrawLimits(double amount) {
    // Update daily and monthly withdrawal limits
    totalWithdrawnDaily += amount;
    totalWithdrawnMonthly += amount;
}

int checkWithdrawalHistory(double amount) {

    if (!checkStatementFile()) {
        return 0; // Return failure if unable to create the transaction file
    }

    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        printf("Error opening transaction file.\n");
        return 0;
    }
    // File exists, proceed with checking withdrawal history...

    double totalMonthlyWithdrawals = 0;
    double totalDailyWithdrawals = 0;

    // Get current date
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);
    char currentMonth[3];
    strftime(currentMonth, sizeof(currentMonth), "%m", currentTime);

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse transaction line
        char *token = strtok(line, ";");
        char *transactionDate = token;

        token = strtok(NULL, ";");
        char *transactionType = token;

        token = strtok(NULL, ";");
        double transactionAmount = atof(token);

        token = strtok(NULL, ";");
        char *username = token;

        // Check if the transaction is from this month and the same user
        if (strncmp(transactionDate, currentMonth, 2) == 0 && strcmp(username, currentUsername) == 0) {
            if (strcmp(transactionType, "Withdraw") == 0) {
                totalMonthlyWithdrawals += transactionAmount;
                if (totalMonthlyWithdrawals > MAX_WITHDRAW_AMOUNT_MONTHLY) {
                    fclose(file);
                    return 0;
                }
            }

            // Check daily withdrawal limit
            if (strncmp(transactionDate, asctime(currentTime), 10) == 0) {
                totalDailyWithdrawals += transactionAmount;
                if (totalDailyWithdrawals > MAX_WITHDRAW_AMOUNT_DAILY) {
                    fclose(file);
                    return 0;
                }
            }
        }
    }

    fclose(file);
    return 1;
}

int withdraw(double amount) {
    // Withdraw money from the account
    if (amount <= 0) {
        printf("Invalid withdrawal amount\n");
        return 0;
    }

    if (currentBalance < amount) {
        printf("Insufficient balance\n");
        return 0;
    }

    if (!canWithdraw(amount, currentUserRole)) {
        return 0;
    }

    // Update account balance and withdrawal limits
    currentBalance -= amount;
    updateWithdrawLimits(amount);
    saveBalanceToFile();

    // Print withdrawal confirmation
    printf("Withdrawal of $%.2f successful\n", amount);

    // Generate withdraw statement
    addNewTransactionRecord(amount, currentUsername, currentUserRole, "Withdraw");

    return 1;
}
