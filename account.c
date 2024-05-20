#include <stdio.h>

double currentBalance;

void readBalanceFromFile() {
    FILE *file = fopen("balance.txt", "r");
    if (file == NULL) {
        // If the file doesn't exist, create it with an initial balance of 1000
        file = fopen("balance.txt", "w");
        if (file == NULL) {
            printf(ANSI_RED ANSI_ITALIC "\nError opening balance file for writing! Please check your system and try again.\n\n" ANSI_RESET);
            return;
        }
        currentBalance = 1000;
        fprintf(file, "%.2f\n", currentBalance);
    } else {
        fscanf(file, "%lf", &currentBalance);
    }
    fclose(file);
}

void saveBalanceToFile() {
    FILE *file = fopen("balance.txt", "w");
    if (file == NULL) {
        printf(ANSI_RED ANSI_ITALIC "\nError opening balance file for writing! Please check your system and try again.\n\n" ANSI_RESET);
        return;
    }
    fprintf(file, "%.2f\n", currentBalance);
    fclose(file);
}

double getCurrentBalance() {
    return currentBalance;
}
