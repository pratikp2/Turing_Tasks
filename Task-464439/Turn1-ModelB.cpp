#include <stdio.h>

int main() {
    int num_elements = 5;
    int array[num_elements] = {1, 2, 3, 4, 5};

    int *array_pointer = array;

    // Visualize the initial memory layout
    printf("Initial memory layout:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("array[%d] = %p: %d\n", i, &array[i], array[i]);
    }

    // Pointer arithmetic: Traversing the array
    printf("\nTraversing the array using pointer:\n");
    for (int *p = array_pointer; p < array_pointer + num_elements; p++) {
        printf("*p = %p: %d\n", p, *p);
    }

    // Changing values using pointer
    printf("\nModifying values using pointer:\n");
    *array_pointer = 10;
    array_pointer++;
    *array_pointer = 20;

    for (int *p = array_pointer; p < array_pointer + num_elements - 2; p++) {
        printf("*p = %p: %d\n", p, *p);
    }

    printf("array[3] = %d\n", array[3]);  // Accessing via array index for demonstration

    // Impact on performance
    printf("\nPerformance impact is usually minor for small arrays, but can be significant for large datasets. ");
    printf("Pointer arithmetic allows for memory-efficient traversal and modification, potentially improving cache coherence and reducing memory access overhead.");

    return 0;
}
