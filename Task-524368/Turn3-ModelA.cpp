#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <chrono>
#include <memory>
#include <vector>

class LogMessage {
public:
    explicit LogMessage(const std::string& message) 
        : message_(new std::string(message)) {}  // Deep copy

    // Deep copy constructor
    LogMessage(const LogMessage& other)
        : message_(new std::string(*other.message_)) {}  

    // Shallow copy constructor (for demonstration)
    LogMessage(std::shared_ptr<std::string> shared_message)
        : message_(shared_message) {}

    LogMessage(LogMessage&& other) noexcept
        : message_(other.message_) { 
        other.message_ = nullptr; 
    }

    LogMessage& operator=(const LogMessage& other) {
        if (this != &other) {
            delete message_;
            message_ = new std::string(*other.message_); 
        }
        return *this;
    }

    LogMessage& operator=(LogMessage&& other) noexcept {
        if (this != &other) {
            delete message_;
            message_ = other.message_;
            other.message_ = nullptr; 
        }
        return *this;
    }

    ~LogMessage() {
        // Only delete if self owned, otherwise handle shared pointers.
        if(message_ && !(message_.use_count() > 1)) {
            delete message_;
        }
    }

    const std::string& getMessage() const { return *message_; }
    
    // Method for shared version
    static LogMessage createShared(const std::string &msg) {
        return LogMessage(std::make_shared<std::string>(msg));
    }

private:
    std::shared_ptr<std::string> message_; // Use shared_ptr for demo of shallow copy
};

class SharedBuffer {
public:
    void produce(const LogMessage& logMessage) {
        std::unique_lock<std::mutex> lock(mutex_);
        buffer_.push(logMessage);
        cv_.notify_one();
    }

    // Consume returns a deep copy of the LogMessage
    LogMessage consume() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !buffer_.empty(); });
        LogMessage msg = buffer_.front();
        buffer_.pop();
        return msg;
    }

private:
    std::queue<LogMessage> buffer_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

void producer(SharedBuffer& buffer, bool useShallowCopy) {
    for (int i = 0; i < 1000; ++i) { // Vary the workload here
        LogMessage logMessage = useShallowCopy
            ? LogMessage::createShared("Log message " + std::to_string(i))
            : LogMessage("Log message " + std::to_string(i));
        buffer.produce(logMessage);
    }
}

void consumer(SharedBuffer& buffer, int& totalMessages) {
    for (int i = 0; i < 1000; ++i) { // Vary the workload here
        LogMessage logMessage = buffer.consume();
        totalMessages++;
    }
}

void benchmark(bool useShallowCopy, int numProducers, int numConsumers) {
    SharedBuffer buffer;
    int totalMessagesProduced = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < numProducers; ++i) {
        producers.emplace_back(producer, std::ref(buffer), useShallowCopy);
    }

    for (int i = 0; i < numConsumers; ++i) {
        consumers.emplace_back(consumer, std::ref(buffer), std::ref(totalMessagesProduced));
    }

    for (auto& prod : producers) {
        prod.join();
    }

    for (auto& cons : consumers) {
        cons.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Total messages processed: " << totalMessagesProduced 
              << " (Using " << (useShallowCopy ? "Shallow" : "Deep") << " Copy)"
              << " Duration: " << duration << " ms" << std::endl;
}

int main() {
    int numProducers = 3;
    int numConsumers = 3;
    
    std::cout << "Benchmarking Deep Copy:" << std::endl;
    benchmark(false, numProducers, numConsumers);

    std::cout << "Benchmarking Shallow Copy:" << std::endl;
    benchmark(true, numProducers, numConsumers);

    return 0;
}
