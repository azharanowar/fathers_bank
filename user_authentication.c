#include <stdio.h>
#include <string.h>
#include "common.c"

void userLoginRegister();
void userLogin();
void registerNewUser();

const char userName[20] = "azharanowar";
const char userPassword[20] = "Huvdhy89pG";


void userLoginRegister()
{
    int userChoice;

    printf("\n\t\033[1;34m**** CHOOSE MENU FROM BELOW ****\033[0m\n\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("\n");

    printf("Enter menu number: ");
    scanf("%i", &userChoice);
    printf("\n");

    if (userChoice == 1) {
        // Login
        loadingAnimation("Login form is loading", 300000);
        userLogin();
    } else if (userChoice == 2) {
        // Register
        void registerNewUser();
    } else {
        printf("\n\033[1;31mWrong menu selection!!! Please enter correct menu number, For login enter: 1 and for register enter: 2.\033[0m\n");
        userLoginRegister(); // Repeating same function again to collect user input another time.
    }
}


void registerNewUser()
{
    // Code for new user registration...
}


void userLogin() {
    char givenUsername[20];
    char givenPassword[20];

    clearInputBuffer();
    printf("Enter your username here: ");
    fgets(givenUsername, 20, stdin);
    givenUsername[strcspn(givenUsername, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter your password here: ");
    fgets(givenPassword, 20, stdin);
    givenPassword[strcspn(givenPassword, "\n")] = '\0'; // Remove trailing newline character


    // Encrypt the password using Caesar cipher with a shift of 3 (for example)
    passwordEncrypt(givenPassword, 7);

    if (strcmp(givenUsername, userName) == 0 && strcmp(givenPassword, userPassword) == 0) {
        printf("Login success!");
    } else {
        printf("Not match");
    }
}
