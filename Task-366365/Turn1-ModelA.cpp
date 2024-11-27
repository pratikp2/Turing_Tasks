#include <atomic>
#include <iostream>
#include <queue>
#include <thread>

std::atomic<bool> queueNotEmpty = false;
std::queue<int> sharedQueue;

void produce() {
    while (true) {
        int item = 1; // Assuming we are producing the same item for simplicity
        sharedQueue.push(item);
        queueNotEmpty.store(true, std::memory_order_release);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consume() {
    while (true) {
        int item;
        queueNotEmpty.load(std::memory_order_acquire);
        
        if (queueNotEmpty) {
            item = sharedQueue.front();
            sharedQueue.pop();
            std::cout << "Consumed item: " << item << std::endl;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

int main() {
    std::thread producer(produce);
    std::thread consumer(consume);

    producer.join();
    consumer.join();

    return 0;
}