#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

class TransactionProcessor {
public:
    TransactionProcessor(int numThreads) : stop(false) {
        // Create worker threads
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(&TransactionProcessor::workerThread, this);
        }
    }

    ~TransactionProcessor() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        cv.notify_all();

        // Join worker threads
        for (auto& thread : threads) {
            thread.join();
        }
    }

    void addTransaction(int transactionId) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            transactions.push(transactionId);
        }
        cv.notify_one();
    }

private:
    void workerThread() {
        while (true) {
            int transactionId;
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock, [this] { return stop || !transactions.empty(); });
                if (stop && transactions.empty()) {
                    return;
                }
                transactionId = transactions.front();
                transactions.pop();
            }

            // Process the transaction
            processTransaction(transactionId);
        }
    }

    void processTransaction(int transactionId) {
        // Simulate transaction processing
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Processed transaction: " << transactionId << std::endl;
    }

    std::vector<std::thread> threads;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<int> transactions;
    bool stop;
};

int main() {
    int numThreads = 4; // Adjust the number of threads based on your system resources
    TransactionProcessor processor(numThreads);

    // Simulate generating transactions
    for (int i = 0; i < 10000; ++i) {
        processor.addTransaction(i);
    }

    return 0;
}