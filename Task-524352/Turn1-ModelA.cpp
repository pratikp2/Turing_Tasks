#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

std::atomic<double> totalTradeVolume(0.0);
std::atomic<double> currentHighestBid(0.0);

// Function for simulating a trading operation
void tradingOperation(int traderId) {
    // Random number generator for simulation
    std::default_random_engine generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(1.0, 100.0); // Trade volumes between 1 and 100
    std::uniform_real_distribution<double> bidDistribution(50.0, 150.0); // Bids between 50 and 150

    for (int i = 0; i < 100; ++i) { // Each trader performs 100 operations
        double volume = distribution(generator);
        double bid = bidDistribution(generator);

        // Update total trade volume atomically
        totalTradeVolume.fetch_add(volume, std::memory_order_relaxed);

        // Atomically update current highest bid if the new bid is higher
        double currentBid = currentHighestBid.load(std::memory_order_relaxed);
        while (bid > currentBid) {
            if (currentHighestBid.compare_exchange_weak(currentBid, bid, std::memory_order_release, std::memory_order_relaxed)) {
                break; // Successfully updated highest bid
            }
            // If the compare_exchange_weak fails, currentBid will be updated with newest value from currentHighestBid
        }
        
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // Simulate processing time
    }
}

int main() {
    const int numTraders = 10;
    std::vector<std::thread> traders;

    // Start multiple trader threads
    for (int i = 0; i < numTraders; ++i) {
        traders.emplace_back(tradingOperation, i);
    }

    // Join all trader threads
    for (auto& trader : traders) {
        trader.join();
    }

    // Display the results
    std::cout << "Total Trade Volume: " << totalTradeVolume.load() << std::endl;
    std::cout << "Current Highest Bid: " << currentHighestBid.load() << std::endl;

    return 0;
}
