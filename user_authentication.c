#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.c"

// Session variables
char currentUsername[20] = "";
int currentUserId = -1;
char currentUserFullName[50] = "";
char currentUserRole[20] = "";

void updateSessionData(int userId);
void userLoginRegister();
void userLogin();
void registerNewUser();
void saveUserData(const char *fullName, const char *email, const char *username, const char *password, const char *userRole);
int getValidUserId(const char *username, const char *password);

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

    printf(ANSI_BOLD);
    printf(ANSI_BG_WHITE "\n\t **** CHOOSE MENU FROM BELOW **** " ANSI_RESET); printf("\n\n");
    printf(" 1. Login\n");
    printf(" 2. Register\n");
    printf("\n");

    printf("Enter menu number: ");
    scanf("%i", &userChoice);
    printf(ANSI_RESET "\n");

    if (userChoice == 1) {
        // Login
        loadingAnimation("Login form is loading", 300000);
        userLogin();

        if (currentUserId != -1) {
            return;
        }
    } else if (userChoice == 2) {
        // Register
        loadingAnimation("Registration form is loading", 30000);
        registerNewUser();
    } else {
        printf("\n\033[1;31mWrong menu selection!!! Please enter correct menu number, For login enter: 1 and for register enter: 2.\033[0m\n");
        userLoginRegister(); // Repeating same function again to collect user input another time.
    }
}

void registerNewUser() {
    User newUser;

    while (1) {
        // Clear input buffer
        clearInputBuffer();

        // Prompt user for full name
        printf("Enter your full name: ");
        fgets(newUser.fullName, sizeof(newUser.fullName), stdin);
        newUser.fullName[strcspn(newUser.fullName, "\n")] = '\0'; // Remove trailing newline character

        // Validate full name
        if (strlen(newUser.fullName) == 0) {
            printf("\n\033[1;31mFull name is mandatory. Please provide your full name.\033[0m\n");
            continue; // Restart loop to prompt for full name again
        }

        // Prompt user for email
        printf("Enter your email: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strcspn(newUser.email, "\n")] = '\0'; // Remove trailing newline character

        // Validate email
        if (strlen(newUser.email) == 0) {
            printf("\n\033[1;31mEmail is mandatory. Please provide your email address.\033[0m\n");
            continue; // Restart loop to prompt for email again
        }

        // Prompt user for username
        printf("Enter your username: ");
        fgets(newUser.username, sizeof(newUser.username), stdin);
        newUser.username[strcspn(newUser.username, "\n")] = '\0'; // Remove trailing newline character

        // Validate username
        if (strlen(newUser.username) == 0) {
            printf("\n\033[1;31mUsername is mandatory. Please provide a username.\033[0m\n");
            continue; // Restart loop to prompt for username again
        }

        // Check if the username already exists
        FILE *userFilePtr = fopen(userFile, "r");
        if (userFilePtr == NULL) {
            perror("Could not open user file");
            exit(EXIT_FAILURE);
        }
        int existingUserId;
        char storedUsername[20], storedPassword[20], storedUserRole[20];
        while (fscanf(userFilePtr, "%d;%*[^;];%*[^;];%[^;];%[^;];%[^\n]", &existingUserId, storedUsername, storedPassword, storedUserRole) != EOF) {
            if (strcmp(newUser.username, storedUsername) == 0) {
                fclose(userFilePtr);
                printf("\n\033[1;31mUsername already exists. Please choose a different username.\033[0m\n");
                continue; // Restart loop to prompt for username again
            }
        }
        fclose(userFilePtr);

        // Prompt user for password
        printf("Enter your password: ");
        fgets(newUser.password, sizeof(newUser.password), stdin);
        newUser.password[strcspn(newUser.password, "\n")] = '\0'; // Remove trailing newline character

        // Validate password
        if (strlen(newUser.password) == 0) {
            printf("\n\033[1;31mPassword is mandatory. Please provide a password.\033[0m\n");
            continue; // Restart loop to prompt for password again
        }

        // Get role choice
        int roleChoice;
        while (1) {
            printf("Select your role:\n");
            printf("1. Father\n");
            printf("2. Child\n");
            printf("Enter your choice: ");
            scanf("%d", &roleChoice);
            clearInputBuffer();

            if (roleChoice == 1) {
                strcpy(newUser.userRole, "Father");
                break;
            } else if (roleChoice == 2) {
                strcpy(newUser.userRole, "Child");
                break;
            } else {
                printf("\nInvalid choice. Please enter 1 for 'Father' or 2 for 'Child'.\n");
            }
        }

        // Encrypt the password using Caesar cipher with a shift of 7 (for example)
        passwordEncrypt(newUser.password, 7);

        // Save user data to file
        saveUserData(newUser.fullName, newUser.email, newUser.username, newUser.password, newUser.userRole);
        
        printf(ANSI_GREEN ANSI_BOLD "\n\n\n" ANSI_RESET);
        printf(ANSI_GREEN ANSI_BOLD ANSI_ITALIC "\nYou have registered successfully! You can now login with your credentials." ANSI_RESET);
        for (int i = 1; i <= 5; i++) {
            printf(ANSI_GREEN ANSI_BOLD "." ANSI_RESET);
            fflush(stdout); // Flush output buffer to display the loading animation immediately
            usleep(300000); // Sleep for 300 milliseconds
        }
        printf("\n\n");
        break; // Exit loop after successful registration
    }

    userLoginRegister(); // Prompt user to login after registration
}



void userLogin() {
    char givenUsername[20];
    char givenPassword[20];

    clearInputBuffer();  
    printf("Enter your username here: ");
    fgets(givenUsername, sizeof(givenUsername), stdin);
    givenUsername[strcspn(givenUsername, "\n")] = '\0'; // Remove trailing newline character
    
    printf("Enter your password here: ");
    fgets(givenPassword, sizeof(givenPassword), stdin);
    givenPassword[strcspn(givenPassword, "\n")] = '\0'; // Remove trailing newline character

    // Encrypt the password using Caesar cipher with a shift of 7 (for example)
    passwordEncrypt(givenPassword, 7);

    int userID = getValidUserId(givenUsername, givenPassword);

    if (userID != -1) {
        printf(ANSI_GREEN ANSI_BOLD ANSI_ITALIC "\nYou have logged in successfully! You will be redirected to your DASHBOARD shortly." ANSI_RESET);
        for (int i = 1; i <= 5; i++) {
            printf(ANSI_GREEN ANSI_BOLD "." ANSI_RESET);
            fflush(stdout); // Flush output buffer to display the loading animation immediately
            usleep(300000); // Sleep for 300 milliseconds
        }
        printf("\n\n");
        
        // Retrieve full name and role of the user from the user data file
        // Assuming the file structure is: userID;fullName;email;username;password;userRole
        char fullName[50]; // Assuming max length of full name is 50 characters
        char userRole[20]; // Assuming max length of role is 20 characters
        FILE *file = fopen(userFile, "r");
        if (file == NULL) {
            perror("Could not open user file");
            exit(EXIT_FAILURE);
        }
        while (fscanf(file, "%*d;%49[^;];%*[^;];%*[^;];%*[^;];%19s", fullName, userRole) != EOF) {
            if (strcmp(givenUsername, fullName) == 0) {
                // Found the user, so break the loop
                break;
            }
        }
        // Close the file after retrieving the full name and role
        fclose(file);
        
        // Save session data with the retrieved full name and role
        updateSessionData(userID);
    } else {
        printf(ANSI_RED ANSI_ITALIC "\nUsername or password doesn't match to our records! Please try again with a valid login credential.\n" ANSI_RESET);
        userLogin();
    }
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

int getValidUserId(const char *username, const char *password) {
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

// Function to update session data
void updateSessionData(int userId) {
    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        perror("Could not open user file");
        exit(EXIT_FAILURE);
    }

    // Loop through the file to find the user with the given user ID
    char line[150]; // Assuming maximum line length in the user file
    while (fgets(line, sizeof(line), file) != NULL) {
        int id;
        char fullName[50], role[20], username[20], password[20];
        sscanf(line, "%d;%49[^;];%49[^;];%19[^;];%19[^;];%19[^;]", &id, fullName, username, password, role);
        if (id == userId) {
            currentUserId = id;
            strcpy(currentUserFullName, fullName);
            strcpy(currentUsername, username);
            strcpy(currentUserRole, role);
            fclose(file);
            return;
        }
    }

    // If user ID not found
    printf("User with ID %d not found.\n", userId);
    fclose(file);
}


