#include <stdio.h>

double currentBalance = 0;

void setBalance(double amount) {
    currentBalance = amount;
}

double getBalance() {
    return currentBalance;
}

void deposit(double amount) {
    currentBalance += amount;
}

void withdraw(double amount) {
    if (amount > currentBalance) {
        printf("Insufficient balance!\n");
    } else {
        currentBalance -= amount;
    }
}
