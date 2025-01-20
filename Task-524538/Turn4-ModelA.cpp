#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>

class EventCounters {
public:
    EventCounters() {
        // Initialize all counters to zero
        for (int i = 0; i < NUM_EVENTS; ++i) {
            counters[i].store(0, std::memory_order_relaxed);
        }
    }

    // Inline function to increment a specific event counter atomically
    inline void increment(int eventType) {
        if (eventType >= 0 && eventType < NUM_EVENTS) {
            counters[eventType].fetch_add(1, std::memory_order_relaxed);
        } else {
            throw std::invalid_argument("Invalid event type");
        }
    }

    // Inline function to get the current value of a specific event counter
    inline int get(int eventType) const {
        if (eventType >= 0 && eventType < NUM_EVENTS) {
            return counters[eventType].load(std::memory_order_acquire);
        } else {
            throw std::invalid_argument("Invalid event type");
        }
    }

private:
    static const int NUM_EVENTS = 3; // Define number of different event types
    std::atomic<int> counters[NUM_EVENTS]; // Array of atomic counters for each event
};

// Function for worker threads to simulate event processing
void eventProcessor(EventCounters& counters, int eventType, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counters.increment(eventType); // Increment the specified event counter
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    const int numThreads = 4;        // Number of worker threads
    const int iterations = 10;       // Number of increments per thread per event type

    EventCounters counters;           // Shared event counters
    std::vector<std::thread> threads; // Vector to hold thread objects

    // Create threads for each event type
    for (int eventType = 0; eventType < EventCounters::NUM_EVENTS; ++eventType) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(eventProcessor, std::ref(counters), eventType, iterations);
        }
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Output the final counts for each event type
    for (int eventType = 0; eventType < EventCounters::NUM_EVENTS; ++eventType) {
        std::cout << "Final count for event type " << eventType << ": " 
                  << counters.get(eventType) << std::endl;
    }

    return 0;
}
