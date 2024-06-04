#include "statement.h"

extern double currentBalance;

#define STATEMENT_FILE "statement.txt"

void addNewTransactionRecord(double amount, const char *username, const char *role, const char *transactionType) {
    FILE *file = fopen(STATEMENT_FILE, "a");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nError opening statement file: %s\n\n" ANSI_RESET, STATEMENT_FILE);
        return;
    }

    // Current time
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", currentTime);

    // Remove any newline characters from username and role
    char cleanUsername[20];
    char cleanRole[20];
    strncpy(cleanUsername, username, sizeof(cleanUsername));
    strncpy(cleanRole, role, sizeof(cleanRole));
    cleanUsername[strcspn(cleanUsername, "\n")] = '\0';
    cleanRole[strcspn(cleanRole, "\n")] = '\0';

    // Write transaction to file including the current balance
    fprintf(file, "%s;%s;%.2f;%s;%s;%.2f\n", timestamp, transactionType, amount, cleanUsername, cleanRole, currentBalance);

    fclose(file);
}

int checkStatementFile() {
    FILE *file = fopen(STATEMENT_FILE, "r");
    if (file == NULL) {
        // If the file doesn't exist, create it and add an initial statement
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nStatement file does not exist! New statement.txt file will be generated now...\n\n" ANSI_RESET);
        file = fopen(STATEMENT_FILE, "w");
        if (file == NULL) {
            system("cls");
            printf(ANSI_RED ANSI_ITALIC "\nError creating statement file: %s\n\n" ANSI_RESET, STATEMENT_FILE);
            return 0; // Return failure if unable to create the file
        }

        // Get initial balance from account.c
        double initialBalance = currentBalance;

        // Add initial deposit transaction with Father role, including the initial balance
        time_t now = time(NULL);
        struct tm *currentTime = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", currentTime);
        fprintf(file, "%s;Deposit;%.2f;UsernameNotApplicable;Father;%.2f\n", timestamp, initialBalance, initialBalance);

        fclose(file); // Close the file after creating it
        return 1; // Return success
    }

    fclose(file);
    return 1; // File exists, return success
}
