#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ready = false;
std::atomic<int>  value = 0;

void producer() {
    for (int i = 0; i < 1000; ++i) {
        value++;
    }
    ready = true;
    std::atomic_thread_fence(std::memory_order_release); // Ensure prior writes are seen
}

void consumer() {
    while (!ready.load()) {
        std::this_thread::yield();
    }
    std::atomic_thread_fence(std::memory_order_acquire); // Ensure subsequent reads see changes
    std::cout << "Consumed value: " << value.load() << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}