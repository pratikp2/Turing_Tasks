#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

const int ARRAY_SIZE = 1000;
std::atomic<int> data_ready = 0;  // Atomic flag to indicate data is ready
int shared_array[ARRAY_SIZE];      // Shared data array

void producer() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        shared_array[i] = i; // Update the shared array
    }
    // Indicate that data is ready
    data_ready.store(1, std::memory_order_release); // Release barrier
}

void consumer() {
    // Wait until data is ready
    while (data_ready.load(std::memory_order_acquire) == 0) {
        std::this_thread::yield(); // or a more efficient wait
    }

    // Access shared array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::cout << "Element " << i << ": " << shared_array[i] << std::endl;
    }
}

int main() {
    std::thread prod_thread(producer);
    std::thread cons_thread(consumer);

    prod_thread.join();
    cons_thread.join();

    return 0;
}
