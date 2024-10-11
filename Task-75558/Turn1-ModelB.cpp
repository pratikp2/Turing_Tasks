#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>

// Message struct
struct Message {
    int data;
};

// Constants
const int NUM_WORKERS = 3;
const int MAX_MESSAGES = 10;

// Global variables
std::queue<Message> messageQueue;
std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> stop(false);

// Worker thread function
void workerThread() {
    while (!stop.load()) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return !messageQueue.empty() || stop.load(); });

        if (!stop.load()) {
            Message msg = messageQueue.front();
            messageQueue.pop();
            lock.unlock();

            // Process the message (Simulate work with a sleep)
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::cout << "Worker processed message: " << msg.data << std::endl;
        }
    }
}

// Main function to send messages and manage failover
int main() {
    // Start worker threads
    std::thread workers[NUM_WORKERS];
    for (int i = 0; i < NUM_WORKERS; ++i) {
        workers[i] = std::thread(workerThread);
    }

    // Send messages to the queue
    for (int i = 1; i <= MAX_MESSAGES; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            Message msg{i};
            messageQueue.push(msg);
        }
        cv.notify_one();
    }

    // Introduce a failure (simulated by stopping one worker)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();

    // Wait for workers to finish
    for (int i = 0; i < NUM_WORKERS; ++i) {
        workers[i].join();
    }

    std::cout << "All messages processed. System shutting down..." << std::endl;
    return 0;
}  
