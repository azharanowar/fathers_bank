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

    printf(ANSI_BOLD ANSI_BG_WHITE "\t **** CHOOSE MENU FROM BELOW **** " ANSI_RESET); printf("\n\n");
    printf(ANSI_BOLD);
    printf(" 1. Login\n");
    printf(" 2. Register\n");
    printf(" 3. Find User\n");
    printf(" 4. Delete User\n");
    printf(" 0. Go to Dashboard\n");

    printf(ANSI_RESET);
    printf("\n");

    printf(ANSI_BOLD ANSI_CYAN ANSI_ITALIC);
    printf("Enter menu number: ");
    scanf("%i", &userChoice);
    printf(ANSI_RESET);

    switch (userChoice)
    {
    case 1:
        system("cls");
        printf(ANSI_BOLD);
        loadingAnimation("Login form is loading", 300000);
        printf(ANSI_RESET);
        userLogin();
        if (currentUserId != -1) {
            return;
        }

        break;
    case 2:
        system("cls");
        printf(ANSI_BOLD);
        loadingAnimation("Registration form is loading", 300000);
        printf(ANSI_RESET);
        registerNewUser();

        break;
    case 3:
        system("cls");
        if (strcmp(currentUserRole, "Father") != 0) {
            printf(ANSI_RED ANSI_ITALIC "You do not have access to this function! It is dedicated for the Father only.\n\n" ANSI_RESET);
            userLoginRegister();
            break;
        }

        findUser();
        userLoginRegister();
        break;
    case 4:
        system("cls");
        if (strcmp(currentUserRole, "Father") != 0) {
            printf(ANSI_RED ANSI_ITALIC "You do not have access to this function! It is dedicated for the Father only.\n\n" ANSI_RESET);
            userLoginRegister();
            break;
        }

        deleteUserByID();
        userLoginRegister();
        break;
    case 0:
        system("cls");
        if (currentUserId != -1) {
            main();
        } else {
            userLoginRegister();
        }
        break;
    default:
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nWrong menu selection!!! Please enter correct menu number.\n" ANSI_RESET);
        userLoginRegister();

        break;
    }

    if (userChoice == 1) {
        
    } else if (userChoice == 2) {
        
    } else {
        
    }
}

void registerNewUser() {
    User newUser;

    while (1) {
        clearInputBuffer();
        printf(ANSI_BOLD ANSI_ITALIC);
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

            char line[100];
            int usernameExists = 0;
            while (fgets(line, sizeof(line), userFilePtr) != NULL) {
                char *token;
                token = strtok(line, ";"); // Skip userID

                token = strtok(NULL, ";"); // Skip fullName
                token = strtok(NULL, ";"); // Skip email

                token = strtok(NULL, ";");
                char storedUsername[20];
                strcpy(storedUsername, token);

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
            printf(ANSI_RED ANSI_ITALIC "Password field is mandatory. Please provide a password. \n\n" ANSI_RESET);
            continue;
        }

        int roleChoice;
        while (1) {
            printf("Select your role:\n");
            printf("1. Father\n");
            printf("2. Child\n");
            printf("Enter your choice: ");
            scanf("%d", &roleChoice);
            clearInputBuffer(); // Clear input buffer after reading integer

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
        printf(ANSI_RESET);

        passwordEncrypt(newUser.password, 7);
        saveUserData(newUser.fullName, newUser.email, newUser.username, newUser.password, newUser.userRole);

        printf(ANSI_GREEN ANSI_BOLD "\n\n\n" ANSI_RESET);
        system("cls");
        printf(ANSI_GREEN ANSI_BOLD ANSI_ITALIC "You have registered successfully! You can now login with your credentials." ANSI_RESET);
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
    printf(ANSI_BOLD ANSI_ITALIC);
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
    } else {
        system("cls");
        printf(ANSI_RED ANSI_ITALIC "\nUsername or password doesn't match with our records! Please try again with valid login credentials.\n" ANSI_RESET);
        userLogin();
    }
    printf(ANSI_RESET);
}

void userLogout() {
    updateSessionData(-1);
    system("cls");
    printf(ANSI_BOLD);
    printf(ANSI_GREEN ANSI_ITALIC "You have successfully logged out! \n\n" ANSI_RESET);
    printf(ANSI_RESET);
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

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        char storedUsername[20], storedPassword[20], storedUserRole[20];

        char *token = strtok(line, ";");
        userID = atoi(token);

        token = strtok(NULL, ";"); // Skip fullName
        token = strtok(NULL, ";"); // Skip email

        token = strtok(NULL, ";");
        strcpy(storedUsername, token);

        token = strtok(NULL, ";");
        strcpy(storedPassword, token);

        token = strtok(NULL, ";");
        strcpy(storedUserRole, token);

        storedUserRole[strcspn(storedUserRole, "\n")] = 0; // Remove newline character

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

        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            int userID;
            char fullName[50], email[50], username[20], password[20], userRole[20];

            char *token = strtok(line, ";");
            userID = atoi(token);

            token = strtok(NULL, ";");
            strcpy(fullName, token);

            token = strtok(NULL, ";");
            strcpy(email, token);

            token = strtok(NULL, ";");
            strcpy(username, token);

            token = strtok(NULL, ";");
            strcpy(password, token);

            token = strtok(NULL, ";");
            strcpy(userRole, token);

            userRole[strcspn(userRole, "\n")] = 0; // Remove newline character

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

void findUser() {
    int searchOption;
    char searchString[50];
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_BG_WHITE " **** FIND USER **** " ANSI_RESET);
    printf("\n\n");

    printf(ANSI_BOLD);
    printf("Choose search option:\n");
    printf("1. By ID\n");
    printf("2. By Username\n");
    printf("3. By Full Name\n");
    printf("4. By Email\n");
    printf("Enter your choice: ");

    scanf("%d", &searchOption);
    // clearInputBuffer(); // Clear input buffer after scanf
    printf(ANSI_RESET);

    printf("\n");
    printf(ANSI_BOLD ANSI_BG_WHITE " **** SEARCH USER **** " ANSI_RESET);
    printf("\n\n");

    switch (searchOption) {
        case 1:
            findUserByID();
            break;
        case 2:
            findUserByUsername();
            break;
        case 3:
            findUserByFullName();
            break;
        case 4:
            findUserByEmail();
            break;
        default:
            printf(ANSI_RED "Invalid search option.\n" ANSI_RESET);
            findUser();
            break;
    }

    return;
}




void findUserByID() {
    int searchID;
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_ITALIC ANSI_BLUE " **** SEARCH USER BY ID **** " ANSI_RESET);
    printf("\n\n");

    printf("Enter user ID to search: ");
    scanf("%d", &searchID);
    clearInputBuffer(); // Clear input buffer after scanf

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf(ANSI_RED "Error opening user file.\n" ANSI_RESET);
        return;
    }

    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        char fullName[50], email[50], username[20];

        // Tokenizing the line to extract individual fields
        char *token = strtok(line, ";");
        userID = atoi(token);

        token = strtok(NULL, ";");
        strcpy(fullName, token);

        token = strtok(NULL, ";");
        strcpy(email, token);

        token = strtok(NULL, ";");
        strcpy(username, token);

        // Removing newline character from username if present
        username[strcspn(username, "\n")] = '\0';

        if (userID == searchID) {
            printf(ANSI_BOLD ANSI_GREEN "\nUser found:\n" ANSI_RESET);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            printf(ANSI_BOLD "ID: " ANSI_RESET ANSI_CYAN "%d\n" ANSI_RESET, userID);
            printf(ANSI_BOLD "Full Name: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, fullName);
            printf(ANSI_BOLD "Email: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, email);
            printf(ANSI_BOLD "Username: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, username);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            found = 1;
            break; // Assuming we want only one match
        }
    }

    fclose(file);

    if (!found) {
        printf(ANSI_RED "User not found.\n" ANSI_RESET);
    }

    printf("\n");
    printf(ANSI_ITALIC);
    printf("Do you want to search again by ID? (Enter Y for yes or any other key for main menu): ");
    scanf(" %c", &toContinue);
    printf(ANSI_RESET);
    printf("\n");

    if (toContinue == 'Y' || toContinue == 'y') {
        findUserByID();
    } else {
        userLoginRegister();
    }
}

void findUserByUsername() {
    char searchString[50];
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_ITALIC ANSI_BLUE " **** SEARCH USER BY USERNAME **** " ANSI_RESET);
    printf("\n\n");

    printf("Enter username to search: ");
    clearInputBuffer();
    fgets(searchString, sizeof(searchString), stdin);
    searchString[strcspn(searchString, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf(ANSI_RED "Error opening user file.\n" ANSI_RESET);
        return;
    }

    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        char fullName[50], email[50], username[20];

        // Tokenizing the line to extract individual fields
        char *token = strtok(line, ";");
        userID = atoi(token);

        token = strtok(NULL, ";");
        strcpy(fullName, token);

        token = strtok(NULL, ";");
        strcpy(email, token);

        token = strtok(NULL, ";");
        strcpy(username, token);

        // Removing newline character from username if present
        username[strcspn(username, "\n")] = '\0';

        if (strcmp(username, searchString) == 0) {
            printf(ANSI_BOLD ANSI_GREEN "\nUser found:\n" ANSI_RESET);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            printf(ANSI_BOLD "ID: " ANSI_RESET ANSI_CYAN "%d\n" ANSI_RESET, userID);
            printf(ANSI_BOLD "Full Name: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, fullName);
            printf(ANSI_BOLD "Email: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, email);
            printf(ANSI_BOLD "Username: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, username);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            found = 1;
            break; // Assuming we want only one match
        }
    }

    fclose(file);

    if (!found) {
        printf(ANSI_RED "User not found.\n" ANSI_RESET);
    }

    printf("\n");
    printf(ANSI_ITALIC);
    printf("Do you want to search again by Username? (Enter Y for yes or any other key for main menu): ");
    scanf(" %c", &toContinue);
    printf(ANSI_RESET);
    printf("\n");

    if (toContinue == 'Y' || toContinue == 'y') {
        findUserByUsername();
    } else {
        userLoginRegister();
    }

}

void findUserByFullName() {
    char searchString[50];
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_ITALIC ANSI_BLUE " **** SEARCH USER BY FULL NAME **** " ANSI_RESET);
    printf("\n\n");

    printf("Enter full name to search: ");
    clearInputBuffer();
    fgets(searchString, sizeof(searchString), stdin);
    searchString[strcspn(searchString, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf(ANSI_RED "Error opening user file.\n" ANSI_RESET);
        return;
    }

    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        char fullName[50], email[50], username[20];

        // Tokenizing the line to extract individual fields
        char *token = strtok(line, ";");
        userID = atoi(token);

        token = strtok(NULL, ";");
        strcpy(fullName, token);

        token = strtok(NULL, ";");
        strcpy(email, token);

        token = strtok(NULL, ";");
        strcpy(username, token);

        // Removing newline character from username if present
        username[strcspn(username, "\n")] = '\0';

        if (strcmp(fullName, searchString) == 0) {
            printf(ANSI_BOLD ANSI_GREEN "\nUser found:\n" ANSI_RESET);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            printf(ANSI_BOLD "ID: " ANSI_RESET ANSI_CYAN "%d\n" ANSI_RESET, userID);
            printf(ANSI_BOLD "Full Name: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, fullName);
            printf(ANSI_BOLD "Email: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, email);
            printf(ANSI_BOLD "Username: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, username);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            found = 1;
            break; // Assuming we want only one match
        }
    }

    fclose(file);

    if (!found) {
        printf(ANSI_RED "User not found.\n" ANSI_RESET);
    }

    printf("\n");
    printf(ANSI_ITALIC);
    printf("Do you want to search again by Full Name? (Enter Y for yes or any other key for main menu): ");
    scanf(" %c", &toContinue);
    printf(ANSI_RESET);
    printf("\n");

    if (toContinue == 'Y' || toContinue == 'y') {
        findUserByFullName();
    } else {
        userLoginRegister();
    }
}

void findUserByEmail() {
    char searchString[50];
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_ITALIC ANSI_BLUE " **** SEARCH USER BY EMAIL **** " ANSI_RESET);
    printf("\n\n");

    printf("Enter email to search: ");
    clearInputBuffer();
    fgets(searchString, sizeof(searchString), stdin);
    searchString[strcspn(searchString, "\n")] = '\0'; // Remove newline character

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf(ANSI_RED "Error opening user file.\n" ANSI_RESET);
        return;
    }

    int found = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        char fullName[50], email[50], username[20];

        // Tokenizing the line to extract individual fields
        char *token = strtok(line, ";");
        userID = atoi(token);

        token = strtok(NULL, ";");
        strcpy(fullName, token);

        token = strtok(NULL, ";");
        strcpy(email, token);

        token = strtok(NULL, ";");
        strcpy(username, token);

        // Removing newline character from username if present
        username[strcspn(username, "\n")] = '\0';

        if (strcmp(email, searchString) == 0) {
            printf(ANSI_BOLD ANSI_GREEN "\nUser found:\n" ANSI_RESET);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            printf(ANSI_BOLD "ID: " ANSI_RESET ANSI_CYAN "%d\n" ANSI_RESET, userID);
            printf(ANSI_BOLD "Full Name: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, fullName);
            printf(ANSI_BOLD "Email: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, email);
            printf(ANSI_BOLD "Username: " ANSI_RESET ANSI_CYAN "%s\n" ANSI_RESET, username);
            printf(ANSI_BOLD "------------------------------\n" ANSI_RESET);
            found = 1;
            break; // Assuming we want only one match
        }
    }

    fclose(file);

    if (!found) {
        printf(ANSI_RED "User not found.\n" ANSI_RESET);
    }

    printf("\n");
    printf(ANSI_ITALIC);
    printf("Do you want to search again by Email? (Enter Y for yes or any other key for main menu): ");
    scanf(" %c", &toContinue);
    printf(ANSI_RESET);
    printf("\n");

    if (toContinue == 'Y' || toContinue == 'y') {
        findUserByEmail();
    } else {
        userLoginRegister();
    }
}

void deleteUserByID() {
    int searchID;
    char toContinue;

    printf("\n");
    printf(ANSI_BOLD ANSI_ITALIC "Enter user ID to delete: " ANSI_RESET);
    scanf("%d", &searchID);
    fflush(stdin);

    FILE *file = fopen(userFile, "r");
    if (file == NULL) {
        printf("Error opening user file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int userID;
        sscanf(line, "%d;", &userID);

        if (userID == searchID) {
            found = 1;
            printf(ANSI_GREEN "User found:\n%s\n" ANSI_RESET, line);
            printf(ANSI_BOLD ANSI_ITALIC "Are you sure you want to delete this user? (Y/N): " ANSI_RESET);
            scanf(" %c", &toContinue);
            fflush(stdin);

            if (toContinue == 'Y' || toContinue == 'y') {
                system("cls");
                printf(ANSI_GREEN ANSI_BOLD "\n\nUser deleted successfully!\n\n" ANSI_RESET);
                continue;
            } else {
                printf( ANSI_RED "\nUser deletion cancelled.\n\n" ANSI_RESET);
            }
        }

        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    remove(userFile);
    rename("temp.txt", userFile);

    if (!found) {
        printf("User not found.\n");
    }
}
