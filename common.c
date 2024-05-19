#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

// ANSI escape codes for text formatting
#define ANSI_RESET      "\x1b[0m"
#define ANSI_BOLD       "\x1b[1m"
#define ANSI_UNDERLINE  "\x1b[4m"
#define ANSI_ITALIC     "\x1b[3m"
#define ANSI_BLACK      "\x1b[30m"
#define ANSI_RED        "\x1b[31m"
#define ANSI_GREEN      "\x1b[32m"
#define ANSI_YELLOW     "\x1b[33m"
#define ANSI_BLUE       "\x1b[34m"
#define ANSI_MAGENTA    "\x1b[35m"
#define ANSI_CYAN       "\x1b[36m"
#define ANSI_WHITE      "\x1b[37m"
#define ANSI_BG_BLACK   "\x1b[40m"
#define ANSI_BG_RED     "\x1b[41m"
#define ANSI_BG_GREEN   "\x1b[42m"
#define ANSI_BG_YELLOW  "\x1b[43m"
#define ANSI_BG_BLUE    "\x1b[44m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN    "\x1b[46m"
#define ANSI_BG_WHITE   "\x1b[47m"

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
    printf(ANSI_ITALIC ANSI_BLUE "%s" ANSI_RESET, loadingText);
    for (int i = 1; i <= 5; i++) {
        printf(ANSI_BLUE "." ANSI_RESET);
        fflush(stdout); // Flush output buffer to display the loading animation immediately
        usleep(millisecond);
    }
    printf("\n\n");
}


