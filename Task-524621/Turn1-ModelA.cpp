#include <stdio.h>
#include <stdlib.h>

size_t custom_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') { // Traverse until null terminator
        length++;
    }
    return length; // Return the length of the string
}

char *custom_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL; // Handle NULL pointers
    }
    
    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0') { // Copying until null terminator
        // No extra operations needed inside the loop
    }
    
    return original_dest; // Return the original destination
}

// Test Function
void test_custom_functions() {
    // Test string for copying
    const char *source = "Hello, world!";
    size_t source_length = custom_strlen(source);
    printf("Length of source string: %zu\n", source_length);

    // Allocate memory for destination
    char *destination = (char *)malloc(source_length + 1); // +1 for the null terminator
    if (destination == NULL) {
        perror("Failed to allocate memory for destination");
        exit(EXIT_FAILURE);
    }

    // Copy string using custom function
    custom_strcpy(destination, source);
    printf("Copied string: %s\n", destination);
    
    // Clean up
    free(destination);
}

int main() {
    test_custom_functions();
    return 0;
}
