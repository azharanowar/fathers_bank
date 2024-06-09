#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


#include "common.c"
#include "user_authentication.c"
#include "account.c"
#include "deposit.c"
#include "withdraw.c"
#include "bill_payments.c"

void showDashboardMenu();

int main() {
    printf("\n");
    printf(ANSI_BOLD ANSI_BG_BLUE " **** WELCOME TO \"FATHER\'S BANK\" **** " ANSI_RESET);
    printf("\n\n");

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
    readBalanceFromFile();
    double amount;

    printf(ANSI_BG_WHITE ANSI_BOLD "\t **** CHOOSE DASHBOARD MENU FROM BELOW **** "ANSI_RESET); printf("\n\n");

    printf(ANSI_BOLD);
    printf(" 1. Check Balance\n");
    printf(" 2. Deposit Money\n");
    printf(" 3. Withdraw Money\n");
    printf(" 4. Bill Payment\n");
    strcmp(currentUserRole, "Father") == 0 ? printf(" 5. View Statement\n") : ' '; // Only show if user role is "Father" with ternary operator
    printf(" 0. Logout\n\n");
    printf(ANSI_RESET);

    printf(ANSI_BOLD ANSI_CYAN ANSI_ITALIC);
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    printf(ANSI_RESET);
    printf("\n");

    char toContinue;
    char confirmProceed;
    switch (choice) {
        case 1:
            system("cls");
            printf(ANSI_BOLD);
            printf("Your current balance is: ");
            printf(ANSI_BG_BLUE " $%.2f " ANSI_RESET, getCurrentBalance());
            printf(ANSI_RESET);
            printf("\n\n");
            usleep(500000);
            showDashboardMenu();
            break;
        case 2:
            system("cls");
            depositMoney();
            showDashboardMenu();
            break;
        case 3:
            system("cls");
            withdrawMoney();
            showDashboardMenu();
            break;
        case 4:
            system("cls");
            billPayments();
            showDashboardMenu();
            break;
        case 5:
            if (strcmp(currentUserRole, "Father") == 0) {
                system("cls");
                displayStatement();
                showDashboardMenu();
            } else {
                printf(ANSI_RED ANSI_ITALIC "You do not have permission to view the statement! Only Father can view the statement.\n\n" ANSI_RESET);
                showDashboardMenu();
            }
            break;
        case 0:
            userLogout();
            main();
            break;
        default:
            printf(ANSI_RED ANSI_ITALIC "Wrong menu choice! Please enter correct menu number to proceed.\n\n" ANSI_RESET);
            showDashboardMenu();
            break;
    }
}
