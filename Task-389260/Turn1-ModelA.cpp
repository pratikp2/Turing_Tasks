#include <iostream>
#include <thread>
#include <atomic>
#include <utility>

// Basic node structure for the stack
struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class LockFreeStack {
private:
    Node* top;
    std::atomic<void*> hazardPtr;

public:
    LockFreeStack() : top(nullptr), hazardPtr(nullptr) {}

    ~LockFreeStack() {
        clean();
    }

    void push(int val) {
        Node* newNode = new Node(val);
        Node* oldTop = nullptr;
        Node* prev = nullptr;
        Node* next = nullptr;

        // Hold the last known top for potential removal
        oldTop = cas(&top, nullptr, newNode);

        // If top was nullptr, it means we have just initialized the stack
        if (oldTop == nullptr) {
            return;
        }

        // Traverse the list to find the position before the new node
        do {
            prev = next;
            next = oldTop->next;
        } while (next != nullptr && cas(&oldTop, oldTop, next) == next);

        // Link the new node after the previous node
        newNode->next = prev;

        // Use a hazard pointer to protect the current top
        setHazardPtr(oldTop);

        // Link the new node to the top
        cas(&top, oldTop, newNode);

        // Release the hazard pointer
        hazardPtr.store(nullptr);
    }

    bool pop(int* val) {
        Node* oldTop = nullptr;
        Node* next = nullptr;

        // Try to hold the top of the stack
        oldTop = cas(&top, top, nullptr);

        // If the stack is empty, return false
        if (oldTop == nullptr) {
            return false;
        }

        // Use a hazard pointer to protect the current top
        setHazardPtr(oldTop);

        // The stack was not empty; try to change the top to the next node
        next = cas(&top, oldTop, oldTop->next);

        // Release the hazard pointer
        hazardPtr.store(nullptr);

        // If successful, we've popped the top node
        if (next == oldTop) {
            *val = oldTop->value;
            delete oldTop;
            return true;
        } else {
            // We failed to pop the top node, rollback
            cas(&top, nullptr, oldTop);
            return false;
        }
    }

    void print() {
        Node* current = top;
        while (current != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    Node* cas(Node** ptr, Node* old, Node* new_val) {
        return static_cast<Node*>(std::atomic_exchange_explicit(
            reinterpret_cast<std::atomic<void*>*>(ptr),
            reinterpret_cast<void*>(new_val),
            reinterpret_cast<void*>(old),
            std::memory_order_acquire,
            std::memory_order_release
        ));
    }

    void setHazardPtr(Node* node) {
        hazardPtr.store(reinterpret_cast<void*>(node));
    }

    void clean() {
        while (true) {
            Node* oldTop = top;
            if (oldTop == nullptr) {
                break;
            }
            Node* next = nullptr;
            do {
                next = oldTop->next;
            } while (next != nullptr && cas(&top, oldTop, next) == next);
            delete oldTop;
        }
    }
};

int main() {
    LockFreeStack stack;

    std::thread worker1([&stack] {
        for (int i = 0; i < 5; ++i) {
            stack.push(i);
        }
    });

    std::thread worker2([&stack] {
        int poppedValue;
        for (int i = 0; i < 5; ++i) {
            if (stack.pop(&poppedValue)) {
                std::cout << "Popped: " << poppedValue << std::endl;
            }
        }
    });

    worker1.join();
    worker2.join();

    stack.print();

    return 0;
}