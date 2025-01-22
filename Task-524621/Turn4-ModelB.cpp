#include <stdio.h>
#include <stdlib.h>

#define USE_UNROLLING

size_t custom_strlen(const char *str) {
    size_t len = 0;

#ifdef USE_UNROLLING
    const char *p = str;

    do {
        len += 8;
        p += 8;
    } while (*p != '\0');

    // Adjust the last few characters that were not fully unrolled
    switch (p - str) {
        case 7: len--; if (*--p == '\0') return len;
        case 6: len--; if (*--p == '\0') return len;
        case 5: len--; if (*--p == '\0') return len;
        case 4: len--; if (*--p == '\0') return len;
        case 3: len--; if (*--p == '\0') return len;
        case 2: len--; if (*--p == '\0') return len;
        case 1: len--; if (*--p == '\0') return len;
    }
    return len + 1; // Add for the '\0' that wasn't unrolled
#else
    while (str[len] != '\0') {
        len++;
    }
    return len;
#endif
}

char *custom_strcpy(char *dest, const char *src) {
#ifdef USE_UNROLLING
    char *d = dest;
    const char *s = src;

    do {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    } while (*s != '\0');

    *d = '\0';
#else
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0');

    *dest = '\0';
    return original_dest;
#endif

    return dest;
}

// Optimized strlen and strcpy functions...

void test_functions() {
    const char *source = "This is a very long string to test the optimized strlen and strcpy functions";
    size_t length = custom_strlen(source);
    printf("Length: %zu\n", length);

    char *destination = (char *)malloc(length + 1);
    if (!destination) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    custom_strcpy(destination, source);
    printf("Copied String: %s\n", destination);

    free(destination);
}

int main() {
    test_functions();
    return 0;
}
