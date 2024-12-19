#include <stdio.h>
#include <stdint.h>

enum FeatureFlags {
    FEATURE1 = 1 << 0, // 0001
    FEATURE2 = 1 << 1, // 0010
    FEATURE3 = 1 << 2  // 0100
};

int main() {
    uint8_t features = 0;

    // Simulating conditions
    // Let's say, it's Tuesday, temperature is above threshold, and the user is active
    features |= FEATURE1 | FEATURE2 | FEATURE3; //features = 0111 (binary)

    // Check conditions using bitwise AND
    if (features & FEATURE1) {
        printf("It's Tuesday.\n");
    }
    if (features & FEATURE2) {
        printf("Temperature is above threshold.\n");
    }
    if (features & FEATURE3) {
        printf("User is active.\n");
    }

    return 0;
}
