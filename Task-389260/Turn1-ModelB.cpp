#include <atomic>
#include <memory>
#include <iostream>

class LockFreeStack {
    private:
     struct Node {
         int data;
         std::shared_ptr<Node> next;

         Node(int data) : data(data), next(nullptr) {}
     };
    
     std::atomic<std::shared_ptr<Node>> head;

    public:
     LockFreeStack() : head(nullptr) {}

     // Push element to the stack
     void push(int data) {
         auto new_node = std::make_shared<Node>(data);
         while (true) {
             new_node->next = head.load(std::memory_order_acquire);
             if (head.compare_exchange_weak(new_node->next, new_node,
                 std::memory_order_release, std::memory_order_acquire)) {
                 break;
             }
         }
     }

     // Pop element from the stack
     bool pop(int& data) {
         while (true) {
             auto old_head = head.load(std::memory_order_acquire);
             if (!old_head) {
                 return false;
             }
             auto next_node = old_head->next;
             if (head.compare_exchange_weak(old_head, next_node,
                 std::memory_order_release, std::memory_order_acquire)) {
                 data = old_head->data;
                 return true;
             }
         }
     }

     bool is_empty() {
         return head.load(std::memory_order_acquire) == nullptr;
     }
 };
 
 // Driver code to test the LockFreeStack implementation
 int main()
 {
     LockFreeStack stack;
     int data = 0;

     // Push some data onto the stack
     stack.push(1);
     stack.push(2);
     stack.push(3);
 
     // Pop data from the stack and display it
     if (stack.pop(data)) {
         std::cout << "Popped element: " << data << std::endl;
     }
     if (stack.pop(data)) {
         std::cout << "Popped element: " << data << std::endl;
     }
     if (stack.pop(data)) {
         std::cout << "Popped element: " << data << std::endl;
     }

     if (stack.is_empty()) {
         std::cout << "Stack is empty." << std::endl;
     } 
     else {
         std::cout << "Stack is not empty." << std::endl;
     }

     return 0;
 }
 