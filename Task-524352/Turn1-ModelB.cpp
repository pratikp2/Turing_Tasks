#include <iostream>
#include <thread>
#include <atomic>
#include <random>
#include <chrono>

#define NUM_THREADS 10
#define NUM_TRADES 100000

std::atomic<int> totalTradeVolume{0};
std::atomic<double> highestBid{0.0};

// Function to generate random trade data and update shared metrics
void simulateTrade(int threadId) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> volumeDist(1, 1000);  // Trade volume between 1 and 1000
    std::uniform_real_distribution<> bidDist(99.0, 101.0);  // Bid price between 99.0 and 101.0

    for (int i = 0; i < NUM_TRADES; ++i) {
        int tradeVolume = volumeDist(gen);
        double bidPrice = bidDist(gen);

        // Update total trade volume atomically
        totalTradeVolume += tradeVolume;

        // Update highest bid atomically using compare_exchange_strong
        double oldBid;
        do {
            oldBid = highestBid.load();
        } while (highestBid.compare_exchange_strong(oldBid, bidPrice, std::memory_order_release, std::memory_order_acquire));
    }
}

int main() {
    std::thread threads[NUM_THREADS];

    // Start multiple threads to simulate concurrent trades
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i] = std::thread(simulateTrade, i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    // Display the final shared metrics
    std::cout << "Total trade volume: " << totalTradeVolume.load() << std::endl;
    std::cout << "Current highest bid: " << highestBid.load() << std::endl;

    return 0;
}
