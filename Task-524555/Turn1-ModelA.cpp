#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <bitset>
#include <chrono>
#include <memory>
#include <mutex>

// Example trade data
struct Trade {
    uint32_t price;
    uint32_t volume;
    uint32_t attributes; // Used for bitwise operations (buy/sell flags)
};

// Class to simulate a market data producer
class TradeProducer {
public:
    void produce(std::queue<Trade>& trades, std::mutex& mutex, std::condition_variable& cv, bool& done) {
        while (!done) {
            Trade trade = {rand() % 100, rand() % 1000, rand() % 4}; // This can represent different states
            {
                std::lock_guard<std::mutex> lock(mutex);
                trades.push(trade);
            }
            cv.notify_one();
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
            uint32_t buyMask = 0b01;      // Bit 0
            uint32_t sellMask = 0b10;     // Bit 1
            if (trade.attributes & buyMask) {
                // Process buy logic
                std::cout << "Processed buy: " << trade.price << " Volume: " << trade.volume << std::endl;
            } 
            if (trade.attributes & sellMask) {
                // Process sell logic
                std::cout << "Processed sell: " << trade.price << " Volume: " << trade.volume << std::endl;
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

    // Start producer and evaluator in threads
    std::thread producerThread(&TradeProducer::produce, &producer, std::ref(trades), std::ref(mutex), std::ref(cv), std::ref(done));
    std::thread evaluatorThread(&TradeEvaluator::evaluate, &evaluator, std::ref(trades), std::ref(mutex), std::ref(cv), std::ref(done));

    // Let it run for 2 seconds for demonstration
    std::this_thread::sleep_for(std::chrono::seconds(2));
    done = true;
    cv.notify_all(); // notify evaluator that we are done

    producerThread.join();
    evaluatorThread.join();

    return 0;
}
