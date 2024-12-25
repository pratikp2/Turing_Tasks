#include <iostream>

// Node structure for linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Function to merge two sorted linked lists
Node* merge(Node* left, Node* right) {
    // Base cases
    if (!left) return right;
    if (!right) return left;

    Node* merged = nullptr;

    // Choose either left or right and recur
    if (left->data <= right->data) {
        merged = left;
        merged->next = merge(left->next, right);
    } else {
        merged = right;
        merged->next = merge(left, right->next);
    }
    return merged;
}

// Function to split the linked list into two halves
void split(Node* head, Node** left, Node** right) {
    Node* fast;
    Node* slow;
    slow = head;
    fast = head->next;

    // Move 'fast' two nodes and 'slow' one node
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // 'slow' is now at the midpoint
    *left = head;
    *right = slow->next;
    slow->next = nullptr; // Split the list into two halves
}

// Merge Sort function for linked list
Node* mergeSort(Node* head) {
    if (!head || !head->next) {
        return head; // Base case: if head is null or there is only one element
    }

    Node* left;
    Node* right;

    // Split the list into two halves
    split(head, &left, &right);

    // Recursively sort the sublists
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

// Function to print the linked list
void printList(Node* node) {
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

// Testing the Merge Sort implementation
int main() {
    Node* head = new Node(5);
    head->next = new Node(1);
    head->next->next = new Node(3);
    head->next->next->next = new Node(2);
    head->next->next->next->next = new Node(4);

    std::cout << "Original List: ";
    printList(head);

    head = mergeSort(head);

    std::cout << "Sorted List: ";
    printList(head);

    // Freeing memory (very important!)
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
