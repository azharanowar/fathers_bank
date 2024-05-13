#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

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
    printf("%s", loadingText);
    for (int i = 1; i <= 5; i++) {
        printf(".");
        fflush(stdout); // Flush output buffer to display the loading animation immediately
        usleep(millisecond); // Sleep for 300 milliseconds
    }
    printf("\n\n");
}


