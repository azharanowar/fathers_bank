#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H


// Session variables
extern int currentUserId;
extern char currentUsername[20];
extern char currentUserFullName[50];
extern char currentUserRole[20];

typedef struct {
    int id;
    char fullName[50];
    char email[50];
    char username[20];
    char password[20];
    char userRole[20];
} User;

void updateSessionData(int userId);
void userLoginRegister();
void userLogin();
void registerNewUser();
void saveUserData(const char *fullName, const char *email, const char *username, const char *password, const char *userRole);
int validateUserLogin(const char *username, const char *password);
void userLogout();
void findUser();
void findUserByID();;
void findUserByUsername();;
void findUserByFullName();;
void findUserByEmail();;
void deleteUserByID();

#endif // USER_AUTHENTICATION_H
