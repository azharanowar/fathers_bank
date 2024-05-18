#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.c"

void userLoginRegister();
void userLogin();
void registerNewUser();
void saveUserData(const char *fullName, const char *email, const char *username, const char *password, const char *userRole);
int getUserId(const char *username, const char *password);
void sessionUserData(int userID);

const char userFile[] = "users.txt";

typedef struct {
    int id;
    char fullName[50];
    char email[50];
    char username[20];
    char password[20];
    char userRole[20];
} User;

void userLoginRegister() {
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
        loadingAnimation("Login form is loading", 15000);
        userLogin();
    } else if (userChoice == 2) {
        // Register
        loadingAnimation("Registration form is loading", 15000);
        registerNewUser();
    } else {
        printf("\n\033[1;31mWrong menu selection!!! Please enter correct menu number, For login enter: 1 and for register enter: 2.\033[0m\n");
        userLoginRegister(); // Repeating same function again to collect user input another time.
    }
}

void registerNewUser() {
    User newUser;

    clearInputBuffer();  
    printf("Enter your full name: ");
    fgets(newUser.fullName, sizeof(newUser.fullName), stdin);
    newUser.fullName[strcspn(newUser.fullName, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter your email: ");
    fgets(newUser.email, sizeof(newUser.email), stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter your username: ");
    fgets(newUser.username, sizeof(newUser.username), stdin);
    newUser.username[strcspn(newUser.username, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter your password: ");
    fgets(newUser.password, sizeof(newUser.password), stdin);
    newUser.password[strcspn(newUser.password, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter your role (father/child): ");
    fgets(newUser.userRole, sizeof(newUser.userRole), stdin);
    newUser.userRole[strcspn(newUser.userRole, "\n")] = '\0'; // Remove trailing newline character

    // Encrypt the password using Caesar cipher with a shift of 7 (for example)
    passwordEncrypt(newUser.password, 7);

    // Save user data to file
    saveUserData(newUser.fullName, newUser.email, newUser.username, newUser.password, newUser.userRole);

    printf("\033[1;32mYou have registered successfully! You can now login with your credentials.\033[0m\n");
    userLoginRegister();
}

void saveUserData(const char *fullName, const char *email, const char *username, const char *password, const char *userRole) {
    FILE *file = fopen(userFile, "a+");
    if (file == NULL) {
        perror("Could not open user file");
        exit(EXIT_FAILURE);
    }

    // Determine the next user ID
    int userID = 1;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int currentID;
        sscanf(line, "%d", &currentID);
        if (currentID >= userID) {
            userID = currentID + 1;
        }
    }

    fprintf(file, "%d;%s;%s;%s;%s;%s\n", userID, fullName, email, username, password, userRole);
    fclose(file);
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

    // Encrypt the password using Caesar cipher with a shift of 7 (for example)
    passwordEncrypt(givenPassword, 7);

    int userID = getUserId(givenUsername, givenPassword);

    if (userID != -1) {
        printf("\033[1;32mYou have logged in successfully! You will be redirected to your DASHBOARD shortly.\033[0m\n");
        sessionUserData(userID);
    } else {
        printf("\n\033[1;31mUsername or password doesn't match our records! Please enter valid login credentials again.\033[0m\n");
        userLogin();
    }
}

int getUserId(const char *username, const char *password) {
    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        perror("Could not open user file");
        exit(EXIT_FAILURE);
    }

    int userID;
    char storedUsername[20], storedPassword[20], storedUserRole[20];
    while (fscanf(file, "%d;%*[^;];%*[^;];%[^;];%[^;];%[^\n]", &userID, storedUsername, storedPassword, storedUserRole) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return userID;
        }
    }

    fclose(file);
    return -1;
}

void sessionUserData(int userID) {
    printf("Welcome, user with ID: %d\n", userID);
    // Additional code for user-specific functionality can be added here
}
