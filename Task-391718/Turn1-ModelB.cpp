#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 20

int main() {
    char name[MAX_NAME_LEN + 1]; // +1 for the null terminator

    printf("Please enter your name: ");
    size_t len = sizeof(name) - 1; // Account for the null terminator
    fgets(name, len, stdin);

    // Remove the newline character if present
    char *p = strchr(name, '\n');
    if (p) {
        *p = '\0';
    }

    // Perform additional input validation (e.g., check for empty string, non-alphanumeric characters, etc.)
    if (strlen(name) == 0) {
        printf("Name cannot be empty.\n");
        return 1;
    }

    printf("Hello, %s!\n", name);

    return 0;
}
