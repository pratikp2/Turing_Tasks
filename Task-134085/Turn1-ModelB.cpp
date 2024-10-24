#include <iostream>
#include <chrono>
#include <vector>

// Function to process events
void processEvents(const std::vector<int>& events) {
    // Simulate event processing time
    for (int event : events) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    // Large number of events to process
    std::vector<int> events(100000);

    // Prepare timer
    std::chrono::high_resolution_clock::time_point start, end;

    // Start the timer
    start = std::chrono::high_resolution_clock::now();

    // Process the events
    processEvents(events);

    // End the timer
    end = std::chrono::high_resolution_clock::now();

    // Calculate and print the elapsed time
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Time taken to process events: " << elapsed.count() << " ms" << std::endl;
    return 0;
}