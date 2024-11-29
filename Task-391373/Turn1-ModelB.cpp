#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    gets(buffer);
    printf("Input: %s\n", buffer);
    return 0;
}
