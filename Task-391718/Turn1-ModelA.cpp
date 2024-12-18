#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 100

void safe_input() {
    char buffer[MAX_INPUT_SIZE];
    
    printf("Enter some input (max %d characters): ", MAX_INPUT_SIZE - 1);
    // Use fgets to read input and limit the size
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Strip newline character if it exists
        buffer[strcspn(buffer, "\n")] = 0;

        // Optional: further validation of buffer content
        if (strlen(buffer) > 0 && strlen(buffer) < MAX_INPUT_SIZE) {
            printf("You entered: %s\n", buffer);
        } else {
            printf("Input is too long or empty.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
}

int main() {
    safe_input();
    return 0;
}
