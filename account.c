#include <stdio.h>

double currentBalance = 1000;

void setBalance(double amount) {
    currentBalance = amount;
}

double getBalance() {
    // printf("%f", currentBalance);
    return currentBalance;
}
