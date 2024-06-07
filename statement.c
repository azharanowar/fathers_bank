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
    char dateTime[20];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", currentTime);

    // Remove any newline characters from username and role
    char cleanUsername[20];
    char cleanRole[20];
    strncpy(cleanUsername, username, sizeof(cleanUsername));
    strncpy(cleanRole, role, sizeof(cleanRole));
    cleanUsername[strcspn(cleanUsername, "\n")] = '\0';
    cleanRole[strcspn(cleanRole, "\n")] = '\0';

    // Write transaction to file including the current balance
    fprintf(file, "%s;%s;%.2f;%s;%s;%.2f\n", dateTime, transactionType, amount, cleanUsername, cleanRole, currentBalance);

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
        char dateTime[20];
        strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", currentTime);
        fprintf(file, "%s;Deposit;%.2f;UsernameNotApplicable;Father;%.2f\n", dateTime, initialBalance, initialBalance);

        fclose(file); // Close the file after creating it
        return 1; // Return success
    }

    fclose(file);
    return 1; // File exists, return success
}

void displayStatement() {
    FILE *file = fopen(STATEMENT_FILE, "r");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nError opening statement file: %s\n\n" ANSI_RESET, STATEMENT_FILE);
        return;
    }

    // Define column widths
    const int dateTimeWidth = 20;
    const int typeWidth = 15;
    const int amountWidth = 10;
    const int userWidth = 20;
    const int roleWidth = 10;
    const int balanceWidth = 12;

    char line[200];

    // Print header
    printf(ANSI_BOLD ANSI_BG_BLUE " %-*s %-*s %-*s %-*s %-*s %-*s " ANSI_RESET "\n",
           dateTimeWidth, "Date & Time",
           typeWidth, "Type",
           amountWidth, "Amount",
           userWidth, "Username",
           roleWidth, "Role",
           balanceWidth, "Balance");

    // Print a line separator
    printf(ANSI_BG_BLUE " %-*s %-*s %-*s %-*s %-*s %-*s " ANSI_RESET "\n",
           dateTimeWidth, "--------------------",
           typeWidth, "---------------",
           amountWidth, "----------",
           userWidth, "--------------------",
           roleWidth, "----------",
           balanceWidth, "------------");

    // Read and print each transaction
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ";");
        char dateTime[dateTimeWidth + 1], type[typeWidth + 1], user[userWidth + 1], role[roleWidth + 1];
        double amount, balance;

        if (token) strncpy(dateTime, token, dateTimeWidth); dateTime[dateTimeWidth] = '\0';
        token = strtok(NULL, ";");
        if (token) strncpy(type, token, typeWidth); type[typeWidth] = '\0';
        token = strtok(NULL, ";");
        if (token) amount = atof(token);
        token = strtok(NULL, ";");
        if (token) strncpy(user, token, userWidth); user[userWidth] = '\0';
        token = strtok(NULL, ";");
        if (token) strncpy(role, token, roleWidth); role[roleWidth] = '\0';
        token = strtok(NULL, ";");
        if (token) balance = atof(token);

        printf(ANSI_BG_WHITE " %-*s %-*s %-*.2f %-*s %-*s %-*.2f " ANSI_RESET "\n",
               dateTimeWidth, dateTime,
               typeWidth, type,
               amountWidth, amount,
               userWidth, user,
               roleWidth, role,
               balanceWidth, balance);
    }

    fclose(file);

    printf("\n");
    printf(ANSI_GREEN ANSI_ITALIC "The statement is ended here..." ANSI_RESET);
    printf("\n\n");

}