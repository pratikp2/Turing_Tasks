#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to perform safe string copy with length check
void safe_strcpy(char* dest, const char* src, size_t dest_size) {
    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        fprintf(stderr, "Memory overflow error: Source string too long.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(dest, src);
}

// Function to perform safe string concatenation with length check
void safe_strcat(char* dest, const char* src, size_t dest_size) {
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    if (dest_len + src_len >= dest_size) {
        fprintf(stderr, "Memory overflow error: Destination string too short.\n");
        exit(EXIT_FAILURE);
    }
    strcat(dest, src);
}

// Function to allocate memory for a string and copy the source
char* allocate_and_copy_string(const char* src) {
    size_t src_len = strlen(src) + 1; // +1 for the null terminator
    char* dest = malloc(src_len);
    if (dest == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    safe_strcpy(dest, src, src_len);
    return dest;
}

int main() {
    char buffer1[10];
    const char* message1 = "Hello, World!";

    safe_strcpy(buffer1, message1, sizeof(buffer1));
    printf("Buffer 1: %s\n", buffer1);

    char buffer2[20];
    const char* message2 = "This is a test message.";

    safe_strcpy(buffer2, message2, sizeof(buffer2));
    safe_strcat(buffer2, " Additional data.", sizeof(buffer2));
    printf("Buffer 2: %s\n", buffer2);

    const char* message3 = "Long message that will cause an overflow if not handled properly.";
    char* buffer3 = allocate_and_copy_string(message3);
    printf("Buffer 3: %s\n", buffer3);

    free(buffer3);

    return 0;
}
