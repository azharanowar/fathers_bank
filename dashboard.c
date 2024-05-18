#include <stdio.h>
#include <stdlib.h>
#include "user_authentication.c"

void showDashboardMenu();

int main() {
    userLoginRegister();
    if (currentUserId != -1) {
        printf("Welcome back, %s!\n\n", currentUserFullName);
        showDashboardMenu();
    } else {
        printf("You are not logged in.\n");
        userLoginRegister();
    }
    return 0;
}

void showDashboardMenu() {
    printf("Dashboard Menu\n");
    printf("1. Check Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Bill Payment\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            // Implement Check Balance function
            break;
        case 2:
            // Implement Deposit function
            break;
        case 3:
            // Implement Withdraw function
            break;
        case 4:
            // Implement Bill Payment function
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}
