#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <thread>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define READ_ITERATIONS 10
#define WRITE_ITERATIONS 5

class DataNode {
public:
    int data;
    std::shared_ptr<DataNode> next;

    DataNode(int value) : data(value), next(nullptr) {}

    ~DataNode() = default;
};

class LinkedList {
private:
    std::shared_ptr<DataNode> head;
    std::shared_mutex mtx;
    std::vector<std::atomic<DataNode*>> hazardPointers;

public:
    LinkedList() : head(nullptr), hazardPointers(NUM_READERS) {}

    // Read operation
    void read() {
        std::shared_lock<std::shared_mutex> rd_lock(mtx);
        auto current = head;
        if (current == nullptr) {
            return;
        }
        // Read using the current pointer, no need to persist it
        std::cout << "Reading data: " << current->data << std::endl;
    }

    // Write operation
    void write() {
        std::unique_lock<std::shared_mutex> wr_lock(mtx);
        
        // Create new node
        auto new_node = std::make_shared<DataNode>(rand() % 100);
        if (!head) {
            head = new_node;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    // Thread-safe operation to delete the node with given data value
    void deleteNode(int dataToDelete) {
        std::unique_lock<std::shared_mutex> wr_lock(mtx);
        
        if (!head) {
            return;
        }

        if (head->data == dataToDelete) {
            std::shared_ptr<DataNode> temp = head;
            head = head->next;
            temp.reset();
            return;
        }

        std::shared_ptr<DataNode> prev = head;
        auto current = head->next;
        while (current) {
            if (current->data == dataToDelete) {
                prev->next = current->next;
                current.reset();
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

void readerThread(LinkedList& list) {
    for (int i = 0; i < READ_ITERATIONS; i++) {
        list.read();
    }
}

void writerThread(LinkedList& list) {
    for (int i = 0; i < WRITE_ITERATIONS; i++) {
        list.write();
        int dataToDelete = rand() % 100;
        std::cout << "Deleting node with data: " << dataToDelete << std::endl;
        list.deleteNode(dataToDelete);
    }
}

int main() {
    LinkedList list;
    std::thread reader_threads[NUM_READERS];
    std::thread writer_threads[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; ++i) {
        reader_threads[i] = std::thread(readerThread, std::ref(list));
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_threads[i] = std::thread(writerThread, std::ref(list));
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        reader_threads[i].join();
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_threads[i].join();
    }

    return 0;
}
