#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HybridDataStructure {
    int array[MAX_ARRAY_SIZE];
    int array_size;
    Node* head;
} HybridDS;

// Function to initialize the hybrid data structure
HybridDS* initialize() {
    HybridDS* hds = (HybridDS*)malloc(sizeof(HybridDS));
    hds->array_size = 0;
    hds->head = NULL;
    return hds;
}

// Function to add an element to the hybrid data structure
void add_element(HybridDS* hds, int data) {
    if (hds->array_size < MAX_ARRAY_SIZE) {
        hds->array[hds->array_size] = data;
        hds->array_size++;
    } else {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = data;
        new_node->next = hds->head;
        hds->head = new_node;
    }
}

// Function to get an element from the array using index
int get_element_from_array(HybridDS* hds, int index) {
    if (index >= 0 && index < hds->array_size) {
        return hds->array[index];
    } else {
        return -1; // Return -1 for invalid index
    }
}

// Function to traverse the linked list
void traverse_linked_list(HybridDS* hds) {
    Node* temp = hds->head;
    printf("Linked List Elements: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free memory (not implemented for simplicity in this example)
void free_hybrid_ds(HybridDS* hds) {
    // Free memory allocated for the array and linked list
    // ...
}

int main() {
    HybridDS* hds = initialize();

    add_element(hds, 1);
    add_element(hds, 8);
    add_element(hds, 4);
    add_element(hds, 2);
    add_element(hds, 13);
    add_element(hds, 7);
    add_element(hds, 5);
    add_element(hds, 3);
    add_element(hds, 11);
    add_element(hds, 6);
    add_element(hds, 9);  // Elements beyond array size will go to linked list

    printf("Array Elements: ");
    for (int i = 0; i < hds->array_size; i++) {
        printf("%d ", hds->array[i]);
    }
    printf("\n");

    traverse_linked_list(hds);

    int element = get_element_from_array(hds, 3);
    if (element != -1) {
        printf("Element at index 3: %d\n", element);
    } else {
        printf("Index out of bounds.\n");
    }