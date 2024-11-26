#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic<bool> ready = false; // Flag to indicate the resource is ready
std::atomic<int>  value = 0;      // Shared resource

void producer() {
    for (int i = 0; i < 1000; ++i) {
        value++; // Increment the shared resource
    }
    ready = true; // Signal that the value is incremented
}

void consumer() {
    while (!ready.load()) { // Wait until the resource is ready
        std::this_thread::yield();
    }

    // The following could erroneously print 0 without memory barriers
    std::cout << "Consumed value: " << value.load() << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}