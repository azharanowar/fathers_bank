// withdraw.c
#include "withdraw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

double getDailyWithdrawn();
double getMonthlyWithdrawn();

int canWithdraw(double amount, const char *currentUserRole);

int withdraw(double amount) {
    // Withdraw money from the account
    if (amount <= 0) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInvalid withdrawal amount! Please enter a valid amount.\n\n" ANSI_RESET);
        return 0;
    }

    if (currentBalance < amount) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nInsufficient balance for withdrawing the amount of $%.2f.\n\n" ANSI_RESET, amount);
        return 0;
    }

    if (!canWithdraw(amount, currentUserRole)) {
        return 0;
    }

    // Update account balance and withdrawal limits
    currentBalance -= amount;
    saveBalanceToFile();

    // Print withdrawal confirmation
    system("cls");
    printf(ANSI_BOLD ANSI_GREEN "Successfully withdrawn the amount of " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, amount);
    printf(ANSI_RESET "\n\n");

    printf(ANSI_BOLD ANSI_GREEN "New account balance is " ANSI_RESET);
    printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, currentBalance);
    printf(ANSI_RESET "\n\n");
    usleep(500000);

    // Generate withdraw statement
    addNewTransactionRecord(amount, currentUsername, currentUserRole, "Withdraw");

    return 1;
}

int canWithdraw(double amount, const char *currentUserRole) {
    if (strcmp(currentUserRole, FATHER_ROLE) == 0) {
        return 1; // Father role can withdraw unlimited
    }

    double totalWithdrawnDaily = getDailyWithdrawn();
    double totalWithdrawnMonthly = getMonthlyWithdrawn();

    // Check daily withdrawal limit
    if ((totalWithdrawnDaily + amount) > MAX_WITHDRAW_AMOUNT_DAILY) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nYour daily withdrawal limit is exceeded! Please try again another day!\n\n" ANSI_RESET);
        return 0;
    }

    // Check monthly withdrawal limit
    if ((totalWithdrawnMonthly + amount) > MAX_WITHDRAW_AMOUNT_MONTHLY) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nYour monthly withdrawal limit is exceeded! Please try again next month!\n\n" ANSI_RESET);
        return 0;
    }

    return 1;
}


double getDailyWithdrawn() {
    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nError opening transaction file.\n\n" ANSI_RESET);
        return 0;
    }

    double totalDailyWithdrawals = 0;

    // Get current date
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", currentTime);

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

        // Check if the transaction is from today and the same user
        if (strncmp(transactionDate, currentDate, 10) == 0 && strcmp(username, currentUsername) == 0) {
            if (strcmp(transactionType, "Withdraw") == 0) {
                totalDailyWithdrawals += transactionAmount;
            }
        }
    }

    fclose(file);
    return totalDailyWithdrawals;
}

double getMonthlyWithdrawn() {
    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nError opening transaction file.\n\n" ANSI_RESET);
        return 0;
    }

    double totalMonthlyWithdrawals = 0;

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
        if (strncmp(transactionDate + 5, currentMonth, 2) == 0 && strcmp(username, currentUsername) == 0) {
            if (strcmp(transactionType, "Withdraw") == 0) {
                totalMonthlyWithdrawals += transactionAmount;
            }
        }
    }

    fclose(file);
    return totalMonthlyWithdrawals;
}