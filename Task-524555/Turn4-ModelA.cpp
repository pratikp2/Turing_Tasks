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

// Structure to represent a dynamic condition
struct Condition {
    uint32_t mask;
    std::string name; // Name for easier debugging/logging
};

// Class to simulate a market data producer
class TradeProducer {
public:
    void produce(std::queue<Trade>& trades, std::mutex& tradeMutex, std::condition_variable& tradeCV, bool& done) {
        // Random number generator
        std::default_random_engine generator;
        std::uniform_int_distribution<int> price_dist(1, 100);
        std::uniform_int_distribution<int> volume_dist(1, 1000);
        std::uniform_int_distribution<int> attribute_dist(0, 3); // 2 bits, max value 3

        while (!done) {
            Trade trade = { price_dist(generator), volume_dist(generator), attribute_dist(generator) };
            {
                std::lock_guard<std::mutex> lock(tradeMutex);
                trades.push(trade);
            }
            tradeCV.notify_one(); // Notify one evaluating thread
            std::this_thread::sleep_for(std::chrono::microseconds(100)); // Simulating delay
        }
    }

    void produceConditions(std::queue<Condition>& conditions, std::mutex& conditionMutex, std::condition_variable& conditionCV, bool& done) {
        // Add dynamic conditions
        std::vector<Condition> conditionsList = {
            {0b01, "BUY"},
            {0b10, "SELL"},
            {0b11, "BOTH"} // Both buy and sell
        };

        for (const auto& condition : conditionsList) {
            {
                std::lock_guard<std::mutex> lock(conditionMutex);
                conditions.push(condition);
            }
            conditionCV.notify_all(); // Notify all evaluating threads that new conditions are available
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating delay
        }
    }
};

// Conditions evaluator, using bitwise operations
class TradeEvaluator {
public:
    void evaluate(std::queue<Trade>& trades, std::mutex& tradeMutex, std::condition_variable& tradeCV, 
                  std::queue<Condition>& conditions, std::mutex& conditionMutex, std::condition_variable& conditionCV, 
                  bool& done) {
        while (!done || !trades.empty()) {
            Trade trade;
            {
                std::unique_lock<std::mutex> lock(tradeMutex);
                tradeCV.wait(lock, [&trades, &done] { return !trades.empty() || done; });
                if (trades.empty())
                    continue;
                trade = trades.front();
                trades.pop();
            }

            // Fetch conditions dynamically
            std::vector<Condition> fetchedConditions;
            {
                std::unique_lock<std::mutex> lock(conditionMutex);
                while (!conditions.empty()) {
                    fetchedConditions.push_back(conditions.front());
                    conditions.pop();
                }
            }

            // Evaluate trade against fetched conditions
            for (const auto& condition : fetchedConditions) {
                if (trade.attributes & condition.mask) {
                    std::cout << "Processed " << condition.name << ": Price = " << trade.price 
                              << ", Volume = " << trade.volume << std::endl;
                }
            }
        }
    }
};

int main() {
    std::queue<Trade> trades;
    std::queue<Condition> conditions;
    std::mutex tradeMutex;
    std::mutex conditionMutex;
    std::condition_variable tradeCV;
    std::condition_variable conditionCV;
    bool done = false;

    TradeProducer producer;
    TradeEvaluator evaluator;

    std::vector<std::thread> evaluatorThreads;
    const int numOfEvalThreads = 4; // Number of evaluator threads

    // Start the producer thread for trades
    std::thread producerThread(&TradeProducer::produce, &producer, std::ref(trades), std::ref(tradeMutex), std::ref(tradeCV), std::ref(done));
    // Start the producer thread for conditions
    std::thread conditionProducerThread(&TradeProducer::produceConditions, &producer, std::ref(conditions), std::ref(conditionMutex), std::ref(conditionCV), std::ref(done));

    // Start evaluation threads
    for (int i = 0; i < numOfEvalThreads; ++i) {
        evaluatorThreads.emplace_back(&TradeEvaluator::evaluate, &evaluator, std::ref(trades), std::ref(tradeMutex), std::ref(tradeCV),
                                      std::ref(conditions), std::ref(conditionMutex), std::ref(conditionCV), std::ref(done));
    }

    // Let it run for 5 seconds for demonstration
    std::this_thread::sleep_for(std::chrono::seconds(5));
    done = true;
    tradeCV.notify_all(); // Notify all waiting trade threads that we are done
    conditionCV.notify_all(); // Notify all waiting condition threads that we are done

    producerThread.join(); // Wait for the producer to finish
    conditionProducerThread.join(); // Wait for condition producer to finish
    for (auto& thread : evaluatorThreads) {
        thread.join(); // Wait for all evaluator threads to finish
    }

    return 0;
}
