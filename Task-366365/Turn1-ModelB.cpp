#include <atomic>

template<typename T>
class AtomicQueue {
private:
    struct Node {
        T data;
        Node* next;
    };

    std::atomic<Node*> head{nullptr};
    std::atomic<Node*> tail{nullptr};

public:
    void push(const T& data) {
        Node* new_node = new Node{data, nullptr};
        Node* old_tail;

        do {
            old_tail = tail.load(std::memory_order_acquire); // Memory barrier: Acquire
        } while (!tail.compare_exchange_weak(old_tail, new_node, std::memory_order_release, std::memory_order_acquire));

        // Once the push is successful, the new node is visible to other threads.
    }

    bool pop(T& data) {
        Node* old_head;

        do {
            old_head = head.load(std::memory_order_acquire);
            if (old_head == nullptr) {
                return false; // Queue is empty
            }

            data = old_head->data;
        } while (!head.compare_exchange_weak(old_head, old_head->next, std::memory_order_release, std::memory_order_acquire));

        // Once the pop is successful, the old node is no longer referenced by the queue.
        delete old_head;
        return true;
    }

    // ... (Other methods)
};