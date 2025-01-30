#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <future>

void processFeed(const std::string& feedName) {
    try {
        while (true) {
            // Simulate processing incoming data
            std::cout << "Processing data from " << feedName << "...\n";

            // Simulate data processing latency
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Replace with actual trading logic
            // For example: if condition occurs, execute trade.
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in " << feedName << ": " << e.what() << "\n";
        // Handle exception appropriately, possibly log or alert.
    }
}

int main() {
    std::vector<std::unique_ptr<SafeThread<void(*)(const std::string&), const std::string&>>> threads;
    std::map<std::string, std::unique_ptr<SafeThread<void(*)(const std::string&), const std::string&>>> threadMap;

    // Simulate multiple data feeds
    std::vector<std::string> feeds = { "NYSE", "NASDAQ", "LSE", "BSE" };

    // Create and start threads for each feed
    for (const auto& feed : feeds) {
        threadMap[feed] = std::make_unique<SafeThread<void(*)(const std::string&), const std::string&>>(processFeed, feed);
    }

    // This demonstration doesn't join threads; you would want to implement a proper termination mechanism.
    // For demonstration, we are relying on the threads to run indefinitely.

    // In production code, you would implement a mechanism to gracefully shut down the threads based on your application needs.

    return 0;
}
