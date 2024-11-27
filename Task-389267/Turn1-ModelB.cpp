#include <iostream>
#include <memory>

// A simple Node class
class Node {
public:
    int data;
    std::unique_ptr<Node> next;

    Node(int data_) : data(data_) {}
};

// Function to add a node at the beginning of the linked list
void push_front(std::unique_ptr<Node>& head, int data) {
    auto new_node = std::make_unique<Node>(data);
    new_node->next = std::move(head);
    head = std::move(new_node);
}

int main() {
    std::unique_ptr<Node> head = nullptr;

    // Dynamically create a linked list
    push_front(head, 5);
    push_front(head, 4);
    push_front(head, 3);

    // Manipulate the linked list using smart pointers
    // ... (your application code goes here)

    // The head will automatically be deleted when it goes out of scope
    // This will free the entire linked list, preventing memory leaks
    return 0;
}