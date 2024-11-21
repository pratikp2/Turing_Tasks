#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = (char *)malloc(100);
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Read input from the user
    fgets(buffer, 200, stdin);

    // Print the input
    printf("Input: %s\n", buffer);

    // Free the allocated memory
    free(buffer);

    return 0;
}