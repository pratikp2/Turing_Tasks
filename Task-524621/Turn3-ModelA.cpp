#include <stdio.h>
#include <stdlib.h>

size_t custom_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

char *custom_strcpy(char *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    
    char *original_dest = dest;
    // Copying until null terminator
    while ((*dest++ = *src++) != '\0');
    
    return original_dest;
}

void test_functions() {
    const char *source = "Hello, world!";
    size_t length = custom_strlen(source);
    printf("Length: %zu\n", length);

    char *destination = (char *)malloc(length + 1); // Allocate memory
    if (!destination) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    custom_strcpy(destination, source);
    printf("Copied String: %s\n", destination);

    free(destination); // Free allocated memory
}

int main() {
    test_functions();
    return 0;
}
