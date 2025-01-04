#include <iostream>
#include <cstdio>
#include <cstdlib>

static int activeCalls = 0;
static size_t totalMemoryAllocated = 0;

void* customMalloc(size_t size) {
    totalMemoryAllocated += size;
    return malloc(size);
}

void customFree(void* ptr, size_t size) {
    totalMemoryAllocated -= size;
    free(ptr);
}

int fibonacci(int n) {
    // Track number of active calls
    activeCalls++;
    printf("Entering fibonacci(%d), Active Calls: %d, Total Memory Allocated: %zu bytes\n", n, activeCalls, totalMemoryAllocated);
    
    if (n <= 1) {
        activeCalls--;
        printf("Exiting fibonacci(%d), Active Calls: %d\n", n, activeCalls);
        return n;
    }

    int left = fibonacci(n - 1);
    int right = fibonacci(n - 2);
    
    activeCalls--;
    printf("Exiting fibonacci(%d), Active Calls: %d\n", n, activeCalls);
    return left + right;
}

int main() {
    int n = 5; // Change this value to see different memory usage
    printf("Fibonacci of %d is %d\n", n, fibonacci(n));
    printf("Total Memory Allocated during execution: %zu bytes\n", totalMemoryAllocated);
    return 0;
}
