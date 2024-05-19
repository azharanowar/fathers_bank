#include <stdio.h>

double currentBalance;

void readBalanceFromFile() {
    FILE *file = fopen("balance.txt", "r");
    if (file == NULL) {
        // If the file doesn't exist, create it with an initial balance of 1000
        file = fopen("balance.txt", "w");
        if (file == NULL) {
            printf("Error creating balance file.\n");
            exit(1);
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
        printf("Error opening balance file for writing.\n");
        exit(1);
    }
    fprintf(file, "%.2f\n", currentBalance);
    fclose(file);
}

double getCurrentBalance() {
    readBalanceFromFile();
    return currentBalance;
}
