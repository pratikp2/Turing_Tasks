#include <stdio.h>
#include <stdlib.h>

// Linked list node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Array of linked lists structure
typedef struct HybridStructure {
    Node** lists;   // Array of pointers to linked lists
    int size;       // Current number of linked lists
    int capacity;   // Max capacity of the array
} HybridStructure;

// Function to create a new linked list node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the hybrid structure
HybridStructure* createHybridStructure(int capacity) {
    HybridStructure* hs = (HybridStructure*)malloc(sizeof(HybridStructure));
    hs->lists = (Node**)malloc(sizeof(Node*) * capacity);
    for (int i = 0; i < capacity; i++) {
        hs->lists[i] = NULL;  // Initialize all linked lists to NULL
    }
    hs->size = 0;
    hs->capacity = capacity;
    return hs;
}

// Function to add a new linked list
void addList(HybridStructure* hs) {
    if (hs->size >= hs->capacity) {
        printf("Cannot add more lists, increase capacity.\n");
        return;
    }
    hs->lists[hs->size++] = NULL; // Create an empty linked list
}

// Function to add a node to a specific list
void addNode(HybridStructure* hs, int listIndex, int data) {
    if (listIndex < 0 || listIndex >= hs->size) {
        printf("Invalid list index.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = hs->lists[listIndex];
    hs->lists[listIndex] = newNode; // Add to the head of the linked list
}

// Function to print a linked list
void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Function to print all lists
void printHybridStructure(HybridStructure* hs) {
    for (int i = 0; i < hs->size; i++) {
        printf("List %d: ", i);
        printList(hs->lists[i]);
    }
}

// Main function
int main() {
    HybridStructure* hs = createHybridStructure(5);
    addList(hs);
    addList(hs);

    addNode(hs, 0, 10);
    addNode(hs, 0, 20);
    addNode(hs, 1, 30);

    printHybridStructure(hs);

    // Free memory (not shown: free each node in lists)
    free(hs->lists);
    free(hs);
    return 0;
}
