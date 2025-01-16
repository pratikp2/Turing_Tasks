#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <chrono>
#include <memory>
#include <vector>
#include <stdexcept> // For std::runtime_error

class LogMessage {
public:
    explicit LogMessage(const std::string& message)
        : message_(std::make_shared<std::string>(message)) {}

    // Deep copy constructor
    LogMessage(const LogMessage& other)
        : message_(std::make_shared<std::string>(*other.message_)) {
        if (!message_) {
            throw std::runtime_error("Failed to copy LogMessage");
        }
    }

    // Shallow copy constructor (shared ownership)
    LogMessage(std::shared_ptr<std::string> shared_message)
        : message_(std::move(shared_message)) {}

    LogMessage(LogMessage&& other) noexcept = default;

    LogMessage& operator=(const LogMessage& other) {
        if (this != &other) {
            message_ = std::make_shared<std::string>(*other.message_);
            if (!message_) {
                throw std::runtime_error("Failed to copy LogMessage");
            }
        }
        return *this;
    }

    LogMessage& operator=(LogMessage&& other) noexcept = default;

    const std::string& getMessage() const { return *message_; }

    // Factory method for shared version
    static LogMessage createShared(const std::string& msg) {
        return LogMessage(std::make_shared<std::string>(msg));
    }

private:
    std::shared_ptr<std::string> message_;
};

class SharedBuffer {
public:
    void produce(const LogMessage& logMessage) {
        // Unique lock for thread safety
        std::unique_lock<std::mutex> lock(mutex_);
        buffer_.push(logMessage);
        cv_.notify_one();
    }

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
    try {
        for (int i = 0; i < 1000; ++i) {
            LogMessage logMessage = useShallowCopy
                ? LogMessage::createShared("Log message " + std::to_string(i))
                : LogMessage("Log message " + std::to_string(i));
            buffer.produce(logMessage);
        }
    } catch (const std::exception& e) {
        std::cerr << "Producer error: " << e.what() << std::endl;
    }
}

void consumer(SharedBuffer& buffer, int& totalMessages) {
    try {
        for (int i = 0; i < 1000; ++i) {
            LogMessage logMessage = buffer.consume();
            totalMessages++;
        }
    } catch (const std::exception& e) {
        std::cerr << "Consumer error: " << e.what() << std::endl;
    }
}

void benchmark(bool useShallowCopy, int numProducers, int numConsumers) {
    SharedBuffer buffer;
    int totalMessagesProduced = 0;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Benchmarking error: " << e.what() << std::endl;
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
