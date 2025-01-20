#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

// Atomic counter class
class AtomicCounter {
public:
    AtomicCounter() : counter(0) {}

    // Inline function to increment the counter atomically
    inline void increment() {
        counter.fetch_add(1, std::memory_order_relaxed);
    }

    // Inline function to decrement the counter atomically
    inline void decrement() {
        counter.fetch_sub(1, std::memory_order_relaxed);
    }

    // Inline function to get the current value of the counter
    inline int get() const {
        return counter.load(std::memory_order_acquire);
    }

private:
    std::atomic<int> counter; // Atomic integer for thread-safe operations
};

// Function to simulate some work and update the counter
void worker(AtomicCounter& counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter.increment();
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    AtomicCounter counter;
    const int numThreads = 4;
    const int iterations = 10;

    std::vector<std::thread> threads;

    // Create and start threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, std::ref(counter), iterations);
    }

    // Wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Output the result
    std::cout << "Final counter value: " << counter.get() << std::endl;

    return 0;
}
