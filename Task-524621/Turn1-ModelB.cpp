#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For original strlen (comparison)

// Custom strcpy function
char *custom_strcpy(char *dest, const char *src) {
    char *cpy_char = dest;
    while (*src) {
        *cpy_char++ = *src++;
    }
    *cpy_char = '\0';
    return dest;
}

// Custom strlen function
size_t custom_strlen(const char *str) {
    size_t len = 0;
    while (*str) {
        str++;
        len++;
    }
    return len;
}

int main() {

    // Example usage of custom strcpy and strlen functions
    const char *source = "Hello, IoT world!";
    char *destination;

    // Malloc memory for the destination string
    destination = malloc(strlen(source) + 1);

    if (destination == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Use custom functions
    char *copied_str = custom_strcpy(destination, source);
    size_t str_len = custom_strlen(source);

    printf("Custom strcpy result: %s\n", copied_str);
    printf("Custom strlen result: String length is %zu\n", str_len);

    // Memory leak check: It's essential to free the dynamically allocated memory
    free(destination);

    return 0;
}
