#include "common.h"

// Function to reset text attributes to default
void resetTextAttributes() {
    printf(ANSI_RESET);
}

// Function to encrypt a string using Caesar cipher
void passwordEncrypt(char *plaintext, int shift) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        // Encrypt uppercase letters
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = ((plaintext[i] - 'A') + shift) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = ((plaintext[i] - 'a') + shift) % 26 + 'a';
        }
        // Encrypt digits
        else if (plaintext[i] >= '0' && plaintext[i] <= '9') {
            plaintext[i] = ((plaintext[i] - '0') + shift) % 10 + '0';
        }
        // Encrypt special characters (assuming ASCII values)
        else if ((plaintext[i] >= 32 && plaintext[i] <= 47) || (plaintext[i] >= 58 && plaintext[i] <= 64) ||
                 (plaintext[i] >= 91 && plaintext[i] <= 96) || (plaintext[i] >= 123 && plaintext[i] <= 126)) {
            plaintext[i] = ((plaintext[i] - 32) + shift) % 95 + 32;
        }
    }
}


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void loadingAnimation(const char *loadingText, int millisecond) {
    // Simulate loading animation
    printf(ANSI_ITALIC ANSI_MAGENTA "%s" ANSI_RESET, loadingText);
    for (int i = 1; i <= 5; i++) {
        printf(ANSI_MAGENTA "." ANSI_RESET);
        fflush(stdout); // Flush output buffer to display the loading animation immediately
        usleep(millisecond);
    }
    printf("\n\n");
}

void removeTrailingWhitespace(char *str) {
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}

int isNumber(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return 0; // Return 0 (false) if any character is not a digit
        }
    }
    return 1; // Return 1 (true) if all characters are digits
}

