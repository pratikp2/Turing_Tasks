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

    // Inline function to get the current value of the counter
    inline int get() const {
        return counter.load(std::memory_order_acquire);
    }

private:
    std::atomic<int> counter; // Atomic integer for thread-safe operations
};

// Function to simulate worker threads
void worker(AtomicCounter& counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter.increment(); // Increment the counter atomically
        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    const int numThreads = 4; // Number of worker threads
    const int iterations = 10; // Number of increments per thread

    AtomicCounter counter; // Shared atomic counter
    std::vector<std::thread> threads; // Vector to hold thread objects

    // Create and start worker threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, std::ref(counter), iterations); // Pass counter by reference
    }

    // Join all threads, waiting for them to finish
    for (auto& t : threads) {
        t.join();
    }

    // Output the final value of the counter
    std::cout << "Final counter value: " << counter.get() << std::endl;

    return 0;
}
