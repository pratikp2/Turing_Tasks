#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <string>

// Atomic counters class
class AtomicCounters {
public:
    AtomicCounters() : counters({{"Event A", 0}, {"Event B", 0}, {"Event C", 0}}) {}

    // Inline function to increment the specified counter atomically
    inline void increment(const std::string& eventType) {
        for (auto& [type, count] : counters) {
            if (type == eventType) {
                count.fetch_add(1, std::memory_order_relaxed);
                return;
            }
        }
        // If the event type is not found, add it with initial count 0
        counters.emplace_back(std::make_pair(eventType, 0));
        counters.back().second.fetch_add(1, std::memory_order_relaxed);
    }

    // Inline function to get the current value of a specific counter
    inline int get(const std::string& eventType) const {
        for (const auto& [type, count] : counters) {
            if (type == eventType) {
                return count.load(std::memory_order_acquire);
            }
        }
        return 0; // Return 0 if the event type is not found
    }

    // Print all counters
    inline void printAllCounters() const {
        std::cout << "Event Counters:\n";
        for (const auto& [type, count] : counters) {
            std::cout << type << ": " << count << std::endl;
        }
    }

private:
    // Use std::vector of std::pair to store event types and their corresponding atomic counters
    std::vector<std::pair<std::string, std::atomic<int>>> counters;
};

// Function to simulate worker threads
void worker(AtomicCounters& counters, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        int randomIndex = i % 3; // Cycle through Event A, Event B, Event C
        const std::string eventTypes[] = {"Event A", "Event B", "Event C"};
        counters.increment(eventTypes[randomIndex]);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    const int numThreads = 4;
    const int iterations = 20;

    AtomicCounters counters;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, std::ref(counters), iterations);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final ";
    counters.printAllCounters();

    return 0;
}
