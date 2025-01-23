#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

// Custom strcpy function
void custom_strcpy(char *destination, const char *source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

// Custom strlen function
size_t custom_strlen(const char *source) {
    size_t length = 0;
    while (source[length] != '\0') {
        length++;
    }
    return length;
}

int main() {
    char input_string[MAX_STRING_LENGTH];
    char copied_string[MAX_STRING_LENGTH];

    printf("Enter a string to analyze: ");
    fgets(input_string, MAX_STRING_LENGTH, stdin);

    // Remove the newline character from the input string
    size_t input_len = custom_strlen(input_string);
    if (input_string[input_len - 1] == '\n') {
        input_string[input_len - 1] = '\0';
    }

    printf("Original string: %s\n", input_string);
    printf("Length of the original string: %zu\n", custom_strlen(input_string));

    custom_strcpy(copied_string, input_string);

    printf("Copied string: %s\n", copied_string);
    printf("Length of the copied string: %zu\n", custom_strlen(copied_string));

    return 0;
}
