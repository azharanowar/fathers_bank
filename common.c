#include <stdio.h>
#include <math.h>
#include <unistd.h>

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


