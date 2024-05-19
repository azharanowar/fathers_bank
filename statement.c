#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int checkStatementFile();

#define TRANSACTION_FILE "statement.txt"

void addNewTransactionRecord(double amount, const char *username, const char *role, const char *transactionType) {
    if (!checkStatementFile()) {
        printf("Error creating transaction file.\n");
        return;
    }

    FILE *file = fopen(TRANSACTION_FILE, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
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

    // Write transaction to file without extra newlines
    fprintf(file, "%s;%s;%.2f;%s;%s\n", timestamp, transactionType, amount, cleanUsername, cleanRole);

    fclose(file);
}

int checkStatementFile() {
    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (file == NULL) {
        // If the file doesn't exist, create it and add an initial transaction
        printf("Statement file does not exist. Creating a new one.\n");
        file = fopen(TRANSACTION_FILE, "w");
        if (file == NULL) {
            printf("Error creating transaction file: %s\n", TRANSACTION_FILE);
            perror("fopen");
            return 0; // Return failure if unable to create the file
        }
        
        // Get initial balance from account.c
        double initialBalance = getCurrentBalance();

        // Add initial deposit transaction with Father role
        time_t now = time(NULL);
        struct tm *currentTime = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", currentTime);
        fprintf(file, "%s;Deposit;%.2f;UsernameNotApplicable;Father\n", timestamp, initialBalance);
        
        fclose(file); // Close the file after creating it
        return 1; // Return success
    }

    fclose(file);
    return 1; // File exists, return success
}
