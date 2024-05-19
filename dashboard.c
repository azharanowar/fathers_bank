#include <stdio.h>
#include <stdlib.h>
#include "user_authentication.c"
#include "account.c"

extern double getBalance();

void showDashboardMenu();

int main() {
    printf(ANSI_BOLD ANSI_BG_BLUE "\n **** WELCOME TO \"FATHER\'S BANK\" **** \n\n" ANSI_RESET);
    userLoginRegister();
    if (currentUserId != -1) {
        printf(ANSI_BOLD ANSI_BG_BLUE " Welcome back, %s! " ANSI_RESET, currentUserFullName);
        printf("\n\n");
        showDashboardMenu();
    } else {
        printf(ANSI_BOLD ANSI_RED "You are not logged in! Please login first to access your Dashboard.\n" ANSI_RESET);
        userLoginRegister();
    }
    return 0;
}

void showDashboardMenu() {
    printf(ANSI_BG_WHITE ANSI_BOLD "\t **** CHOOSE DASHBOARD MENU FROM BELOW **** "ANSI_RESET); printf("\n\n");

    printf(ANSI_BOLD);
    printf(" 1. Check Balance\n");
    printf(" 2. Deposit Money\n");
    printf(" 3. Withdraw Money\n");
    printf(" 4. Bill Payment\n");
    printf(" 5. Logout\n\n");

    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    printf(ANSI_RESET);
    printf("\n");

    switch (choice) {
        case 1:
            
            printf(ANSI_BOLD);
            printf("Your current balance is: ");
            printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, getBalance());
            printf(ANSI_RESET);
            printf("\n\n");
            usleep(500000);
            showDashboardMenu();
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
        case 5:
            // Implement Logout function
            break;
        default:
            printf(ANSI_RED ANSI_ITALIC "Wrong menu choice! Please enter 1-5 to select menu.\n\n" ANSI_RESET);
            showDashboardMenu();
            break;
    }
}
