#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>


// Function to encrypt a string using Caesar cipher
void passwordEncrypt(char *plainPassword, int shift) {
    int i;
    for (i = 0; i < strlen(plainPassword); i++) {
        // Encrypt uppercase letters
        if (plainPassword[i] >= 'A' && plainPassword[i] <= 'Z') {
            plainPassword[i] = ((plainPassword[i] - 'A') + shift) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (plainPassword[i] >= 'a' && plainPassword[i] <= 'z') {
            plainPassword[i] = ((plainPassword[i] - 'a') + shift) % 26 + 'a';
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
    for (int i = 1; i < 2; i++) {
        printf(".");
        fflush(stdout); // Flush output buffer to display the loading animation immediately
        usleep(millisecond); // Sleep for 300 milliseconds
    }
    printf("\n\n");
}


