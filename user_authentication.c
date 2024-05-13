#include <stdio.h>
#include <string.h>

void userLoginRegister()
{
    int userChoice;

    printf("**** CHOOSE MENU FROM BELOW ****\n\n");
    printf("1. Login\n");
    printf("2. Register\n");

    printf("Enter menu number: ");
    scanf("%i", &userChoice);

    if (userChoice == 1) {
        // Login
        userLogin();
    } else if (userChoice == 2) {
        // Register
        registerNewUser();
    } else {
        printf("Wrong menu selection!!! Please enter correct menu number, 1 for login and 2 for regiter.");
    }
}


void registerNewUser()
{
    // Code for new user registration...
}

void userLogin()
{

}

