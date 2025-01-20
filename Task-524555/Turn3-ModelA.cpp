#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <bitset>
#include <chrono>
#include <mutex>
#include <random>

// Example trade data structure
struct Trade {
    uint32_t price;
    uint32_t volume;
    uint32_t attributes; // Used for bitwise operations (buy/sell/hold flags)
};

// Class to simulate a market data producer
class TradeProducer {
public:
    void produce(std::queue<Trade>& trades, std::mutex& mutex, std::condition_variable& cv, bool& done) {
        // Random number generator
        std::default_random_engine generator;
        std::uniform_int_distribution<int> price_dist(1, 100);
        std::uniform_int_distribution<int> volume_dist(1, 1000);
        std::uniform_int_distribution<int> attribute_dist(0, 3); // 2 bits, max value 3

        while (!done) {
            Trade trade = { price_dist(generator), volume_dist(generator), attribute_dist(generator) };
            {
                std::lock_guard<std::mutex> lock(mutex);
                trades.push(trade);
            }
            cv.notify_one(); // Notify one evaluating thread
            std::this_thread::sleep_for(std::chrono::microseconds(100)); // Simulating delay
        }
    }
};

// Conditions evaluator, using bitwise operations
class TradeEvaluator {
public:
    void evaluate(std::queue<Trade>& trades, std::mutex& mutex, std::condition_variable& cv, bool& done) {
        while (!done || !trades.empty()) {
            Trade trade;
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock, [&trades, &done] { return !trades.empty() || done; });
                if (trades.empty())
                    continue;
                trade = trades.front();
                trades.pop();
            }

            // Example bitwise evaluation conditions
            uint32_t buyMask = 0b01;      // Bit 0: Buy
            uint32_t sellMask = 0b10;     // Bit 1: Sell

            // Bitwise checks using AND
            if (trade.attributes & buyMask) {
                std::cout << "Processed BUY: Price = " << trade.price << ", Volume = " << trade.volume << std::endl;
            }
            if (trade.attributes & sellMask) {
                std::cout << "Processed SELL: Price = " << trade.price << ", Volume = " << trade.volume << std::endl;
            }
        }
    }
};

int main() {
    std::queue<Trade> trades;
    std::mutex mutex;
    std::condition_variable cv;
    bool done = false;

    TradeProducer producer;
    TradeEvaluator evaluator;

    std::vector<std::thread> evaluatorThreads;
    const int numOfEvalThreads = 4; // Number of evaluator threads

    // Start producer thread
    std::thread producerThread(&TradeProducer::produce, &producer, std::ref(trades), std::ref(mutex), std::ref(cv), std::ref(done));

    // Start evaluation threads
    for (int i = 0; i < numOfEvalThreads; ++i) {
        evaluatorThreads.emplace_back(&TradeEvaluator::evaluate, &evaluator, std::ref(trades), std::ref(mutex), std::ref(cv), std::ref(done));
    }

    // Let it run for 5 seconds for demonstration
    std::this_thread::sleep_for(std::chrono::seconds(5));
    done = true;
    cv.notify_all(); // Notify all waiting threads that we are done

    producerThread.join(); // Wait for the producer to finish
    for (auto& thread : evaluatorThreads) {
        thread.join(); // Wait for all evaluator threads to finish
    }

    return 0;
}
