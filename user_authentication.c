#include "user_authentication.h"
#include "common.h"

// Session variables
int currentUserId = -1;
char currentUsername[20] = "";
char currentUserFullName[50] = "";
char currentUserRole[20] = "";

const char userFile[] = "users.txt";

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
        system("cls");
        loadingAnimation("Login form is loading", 300000);
        userLogin();
        if (currentUserId != -1) {
            return;
        }
    } else if (userChoice == 2) {
        system("cls");
        loadingAnimation("Registration form is loading", 300000);
        registerNewUser();
    } else {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nWrong menu selection!!! Please enter correct menu number, For login enter: 1 and for register enter: 2.\n" ANSI_RESET);
        userLoginRegister();
    }
}

void registerNewUser() {
    User newUser;

    while (1) {
        clearInputBuffer();
        printf("Enter your full name: ");
        fgets(newUser.fullName, sizeof(newUser.fullName), stdin);
        newUser.fullName[strcspn(newUser.fullName, "\n")] = '\0';
        if (strlen(newUser.fullName) == 0) {
            printf(ANSI_RED ANSI_ITALIC "Full name field is mandatory. Please provide your full name. \n\n" ANSI_RESET);
            continue;
        }

        printf("Enter your email: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strcspn(newUser.email, "\n")] = '\0';
        if (strlen(newUser.email) == 0) {
            printf(ANSI_RED ANSI_ITALIC "Email address is mandatory. Please provide your email address. \n\n" ANSI_RESET);
            continue;
        }

        while (1) {
            printf("Enter your username: ");
            fgets(newUser.username, sizeof(newUser.username), stdin);
            newUser.username[strcspn(newUser.username, "\n")] = '\0';
            if (strlen(newUser.username) == 0) {
                printf(ANSI_RED ANSI_ITALIC "Username is mandatory. Please provide a username. \n\n" ANSI_RESET);
                continue;
            }

            FILE *userFilePtr = fopen(userFile, "r");
            if (userFilePtr == NULL) {
                perror("Could not open user file");
                exit(EXIT_FAILURE);
            }

            int existingUserId;
            char storedUsername[20], storedPassword[20], storedUserRole[20];
            int usernameExists = 0;
            while (fscanf(userFilePtr, "%d;%*[^;];%*[^;];%[^;];%[^;];%[^\n]", &existingUserId, storedUsername, storedPassword, storedUserRole) != EOF) {
                if (strcmp(newUser.username, storedUsername) == 0) {
                    usernameExists = 1;
                    break;
                }
            }
            fclose(userFilePtr);

            if (usernameExists) {
                printf(ANSI_RED ANSI_ITALIC "Username already exists. Please choose a different username. \n\n" ANSI_RESET);
            } else {
                break;
            }
        }

        printf("Enter your password: ");
        fgets(newUser.password, sizeof(newUser.password), stdin);
        newUser.password[strcspn(newUser.password, "\n")] = '\0';
        if (strlen(newUser.password) == 0) {
            printf(ANSI_RED ANSI_ITALIC "Password is mandatory. Please provide a password. \n\n" ANSI_RESET);
            continue;
        }

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
                printf(ANSI_RED ANSI_ITALIC "\nInvalid choice. Please enter 1 for 'Father' or 2 for 'Child'.\n" ANSI_RESET);
            }
        }

        passwordEncrypt(newUser.password, 7);
        saveUserData(newUser.fullName, newUser.email, newUser.username, newUser.password, newUser.userRole);

        printf(ANSI_GREEN ANSI_BOLD "\n\n\n" ANSI_RESET);
        system("cls");
        printf(ANSI_GREEN ANSI_BOLD ANSI_ITALIC "\nYou have registered successfully! You can now login with your credentials." ANSI_RESET);
        for (int i = 1; i <= 5; i++) {
            printf(ANSI_GREEN ANSI_BOLD "." ANSI_RESET);
            fflush(stdout);
            usleep(300000);
        }
        printf("\n\n");
        break;
    }

    userLoginRegister();
}

void userLogin() {
    char givenUsername[20];
    char givenPassword[20];

    clearInputBuffer();
    printf("Enter your username here: ");
    fgets(givenUsername, sizeof(givenUsername), stdin);
    givenUsername[strcspn(givenUsername, "\n")] = '\0';

    printf("Enter your password here: ");
    fgets(givenPassword, sizeof(givenPassword), stdin);
    givenPassword[strcspn(givenPassword, "\n")] = '\0';

    passwordEncrypt(givenPassword, 7);
    int userID = validateUserLogin(givenUsername, givenPassword);

    if (userID != -1) {
        system("cls");
        printf(ANSI_GREEN ANSI_BOLD ANSI_ITALIC "\nYou have logged in successfully! You will be redirected to your DASHBOARD shortly." ANSI_RESET);
        for (int i = 1; i <= 5; i++) {
            printf(ANSI_GREEN ANSI_BOLD "." ANSI_RESET);
            fflush(stdout);
            usleep(300000);
        }
        printf("\n\n");
        system("cls");
    } else {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nUsername or password doesn't match our records! Please try again with valid login credentials.\n" ANSI_RESET);
        system("cls");
        userLogin();
    }
}

void userLogout() {
    updateSessionData(-1);
    system("cls");
    printf(ANSI_GREEN ANSI_ITALIC "You have successfully logged out! \n\n" ANSI_RESET);
    system("cls");
}

void saveUserData(const char *fullName, const char *email, const char *username, const char *password, const char *userRole) {
    FILE *file = fopen(userFile, "a+");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nUser file could not open! Please check your system and try again.\n\n" ANSI_RESET);
        return;
    }

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

int validateUserLogin(const char *username, const char *password) {
    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nUser file could not open! Please check your system and try again.\n\n" ANSI_RESET);
        return -1;
    }

    int userID;
    char storedUsername[20], storedPassword[20], storedUserRole[20];
    while (fscanf(file, "%d;%*[^;];%*[^;];%[^;];%[^;];%[^\n]", &userID, storedUsername, storedPassword, storedUserRole) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            updateSessionData(userID);
            return userID;
        }
    }

    fclose(file);
    return -1;
}

void updateSessionData(int userId) {
    currentUserId = userId;
    if (userId == -1) {
        strcpy(currentUsername, "");
        strcpy(currentUserFullName, "");
        strcpy(currentUserRole, "");
    } else {
        FILE *file = fopen(userFile, "r");
        if (file == NULL) {
            system("cls");
            printf(ANSI_RED ANSI_ITALIC "\nUser file could not open! Please check your system and try again.\n\n" ANSI_RESET);
            return;
        }

        int userID;
        char fullName[50], email[50], username[20], password[20], userRole[20];
        while (fscanf(file, "%d;%[^;];%[^;];%[^;];%[^;];%[^\n]", &userID, fullName, email, username, password, userRole) != EOF) {
            if (userID == userId) {
                strcpy(currentUsername, username);
                strcpy(currentUserFullName, fullName);
                strcpy(currentUserRole, userRole);
                break;
            }
        }
        fclose(file);
    }
}
