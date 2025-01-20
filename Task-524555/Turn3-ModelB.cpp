#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <bitset>
#include <random>
#include <mutex>
#include <cstdlib> // For rand()

struct Trade {
    uint32_t price;
    uint32_t volume;
    uint32_t attributes; // Bitmask to represent conditions (e.g., 0b01 for buy, 0b10 for sell, 0b11 for both)
};

class TradeProcessor {
public:
    TradeProcessor(size_t num_threads) : num_threads(num_threads) {
    }

    void start() {
        for (size_t i = 0; i < num_threads; ++i) {
            worker_threads.emplace_back(std::thread(&TradeProcessor::process_trades, this));
        }
    }

    void wait_for_completion() {
        for (auto& thread : worker_threads) {
            thread.join();
        }
    }

    void process_trades() {
        while (true) {
            Trade trade;
            {
                std::unique_lock<std::mutex> lock(mutex);
                condition.wait(lock, [this] { return !trades.empty() || stop; });
                if (trades.empty() && stop) {
                    return;
                }
                trade = trades.front();
                trades.pop();
            }

            // Bitwise conditional checks
            const uint32_t buyMask = 0b01;
            const uint32_t sellMask = 0b10;

            if (trade.attributes & buyMask) {
                handle_trade(trade, "Buy");
            }

            if (trade.attributes & sellMask) {
                handle_trade(trade, "Sell");
            }
        }
    }

    void enqueue_trade(Trade trade) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            trades.push(trade);
        }
        condition.notify_one();
    }

    void stop_workers() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
    }

private:
    size_t num_threads;
    std::vector<std::thread> worker_threads;
    std::queue<Trade> trades;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop = false;

    void handle_trade(const Trade& trade, const std::string& type) {
        std::cout << "Thread " << std::this_thread::get_id() << ": Processed " << type << " trade: Price " << trade.price << ", Volume " << trade.volume << std::endl;
    }
};

int main() {
    const size_t num_threads = 4;
    const size_t num_trades = 10000;

    TradeProcessor processor(num_threads);
    processor.start();

    // Generate and enqueue trades
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> price_dist(1, 1000);
    std::uniform_int_distribution<> volume_dist(1, 1000);
    std::uniform_int_distribution<> attribute_dist(0, 3); // 0 for none, 1 for buy, 2 for sell, 3 for both

    for (size_t i = 0; i < num_trades; ++i) {
        Trade trade = {price_dist(gen), volume_dist(gen), attribute_dist(gen)};
        processor.enqueue_trade(trade);
    }

    processor.stop_workers();
    processor.wait_for_completion();

    std::cout << "Processing complete." << std::endl;
    return 0;
}
