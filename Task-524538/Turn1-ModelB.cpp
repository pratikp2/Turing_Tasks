#include <atomic>
#include <iostream>
#include <thread>

// Inline function for atomic increment
inline void atomic_increment(std::atomic<int>& counter) {
    ++counter;
}

// Inline function for atomic decrement
inline void atomic_decrement(std::atomic<int>& counter) {
    --counter;
}

// Inline function for atomic fetch and add
inline int atomic_fetch_and_add(std::atomic<int>& counter, int value) {
    return counter.fetch_add(value);
}

// Inline function for atomic compare and exchange
inline bool atomic_compare_and_exchange(std::atomic<int>& counter, int expected, int desired) {
    return counter.compare_exchange_strong(expected, desired);
}

// Example usage
int main() {
    const int num_threads = 10;
    const int num_iterations = 100000;

    std::atomic<int> shared_counter = 0;

    // Launch threads that perform atomic operations
    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([&shared_counter, num_iterations] {
            for (int j = 0; j < num_iterations; ++j) {
                atomic_increment(shared_counter);
                atomic_decrement(shared_counter);
                int new_value = atomic_fetch_and_add(shared_counter, 5);
                // Simulate some work with the new value
                std::this_thread::sleep_for(std::chrono::nanoseconds(100));
                atomic_fetch_and_add(shared_counter, -5);
            }
        });
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final value of the shared counter
    std::cout << "Final value of shared_counter: " << shared_counter << std::endl;

    return 0;
}
