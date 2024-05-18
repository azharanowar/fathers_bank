// withdraw.c

#include <stdio.h>

void withdraw(double *balance, double amount) {
    if (*balance >= amount) {
        *balance -= amount;
        printf("\n$%.2f withdrawn successfully.\n", amount);
    } else {
        printf("\nInsufficient funds! Cannot withdraw $%.2f\n", amount);
    }
}
