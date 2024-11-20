#include <stdio.h>
#include <string.h>

void safe_strcpy(char *dest, const char *src, size_t len) {
    size_t i;
    for (i = 0; i < len && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int main() {
    char buffer[10];
    safe_strcpy(buffer, "Hello, World!", sizeof(buffer));
    printf("Buffer: %s\n", buffer);
    return 0;
}