#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <bitset>
#include <random>
#include <chrono>
#include <unordered_map>
#include <functional>

// Global constant for the number of dynamic conditions
const int NUM_DYNAMIC_CONDITIONS = 8;

// Bitwise masks for conditions
const std::array<uint32_t, NUM_DYNAMIC_CONDITIONS> CONDITION_MASKS = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000
};

// Trade structure
struct Trade {
    uint32_t price;
    uint32_t volume;
    uint32_t attributes; // Attributes that will be matched with dynamic conditions
};

// Structure to hold a dynamic condition
struct Condition {
    uint32_t mask;
    std::function<void(const Trade&)> action; // Action to be performed when condition is matched
};

class TradeEvaluator {
public:
    TradeEvaluator(std::queue<Condition>& conditionQueue, std::mutex& conditionMutex, std::condition_variable& conditionCV)
        : conditionQueue(conditionQueue), conditionMutex(conditionMutex), conditionCV(conditionCV) {}

    void evaluate(std::queue<Trade>& trades, std::mutex& tradesMutex, bool& done) {
        while (!done || !trades.empty()) {
            Trade trade;
            {
                std::unique_lock<std::mutex> lock(tradesMutex);
                conditionCV.wait(lock, [&trades, &done] { return !trades.empty() || done; });
                if (trades.empty())
                    continue;
                trade = trades.front();
                trades.pop();
            }

            // Check all conditions
            for (auto& condition : conditionQueue) {
                if (trade.attributes & condition.mask) {
                    // Execute the associated action
                    condition.action(trade);
                }
            }
        }
    }

private:
    std::queue<Condition>& conditionQueue;
    std::mutex& conditionMutex;
    std::condition_variable& conditionCV;
};

class ConditionUpdater {
public:
    ConditionUpdater(std::queue<Condition>& conditionQueue, std::mutex& conditionMutex, std::condition_variable& conditionCV)
        : conditionQueue(conditionQueue), conditionMutex(conditionMutex), conditionCV(conditionCV) {}

    void updateConditions(const std::vector<Condition>& newConditions) {
        {
            std::unique_lock<std::mutex> lock(conditionMutex);
            conditionQueue = newConditions;
        }
        conditionCV.notify_all();
    }

private:
    std::queue<Condition>& conditionQueue;
    std::mutex& conditionMutex;
    std::condition_variable& conditionCV;
};

int main() {
    std::queue<Trade> trades;
    std::mutex tradesMutex;
    std::condition_variable tradesCV;

    std::queue<Condition> conditionQueue;
    std::mutex conditionMutex;
    std::condition_variable conditionCV;

    bool done = false;

    TradeProducer producer(trades, tradesMutex, tradesCV, done);
    ConditionUpdater conditionUpdater(conditionQueue, conditionMutex, conditionCV);

    // Initialize some dynamic conditions
    std::vector<Condition> initialConditions = {
        { CONDITION_MASKS[0], [](const Trade& trade) { std::cout << "Processed Condition 1: BUY, Price = " << trade.price << ", Volume = " << trade.volume << std::endl; } },
        { CONDITION_MASKS[3], [](const Trade& trade) { std::cout << "Processed Condition 4: SELL, Price = " << trade.price << ", Volume = " << trade.volume << std::endl; } },
    };
    conditionUpdater.updateConditions(initialConditions);

    std::vector<std::thread> evaluatorThreads;
    const int numOfEvalThreads = 4;

    // Start evaluator threads
    for (int i = 0; i < numOfEvalThreads; ++i) {
        TradeEvaluator evaluator(conditionQueue, conditionMutex, conditionCV);
        evaluatorThreads.emplace_back([&evaluator, &trades, &tradesMutex, &done] { evaluator.evaluate(trades, tradesMutex, done); });
    }

    // Start producer thread
    std::thread producerThread([&producer] { producer.produce(); });

    // Simulate condition updates at runtime
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::vector<Condition> updatedConditions = {
        { CONDITION_MASKS[1], [](const Trade& trade) { std::cout << "Processed Condition 2: HOLD, Price = " << trade.price << ", Volume = " << trade.volume << std::endl; } },
        { CONDITION_MASKS[7], [](const Trade& trade) { std::cout << "Processed Condition 8: OTHER, Price = " << trade.price << ", Volume = " << trade.volume << std::endl; } },
    };
    conditionUpdater.updateConditions(updatedConditions);

    // Let it run for another 3 seconds
    std::this_thread::sleep_for(std::chrono::seconds(3));

    done = true;
    tradesCV.notify_all();

    producerThread.join();
    for (auto& thread : evaluatorThreads) {
        thread.join();
    }

    return 0;
}
