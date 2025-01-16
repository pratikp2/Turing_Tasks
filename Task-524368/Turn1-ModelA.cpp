#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <chrono>
#include <memory>

class LogMessage {
public:
    explicit LogMessage(const std::string& message)
        : message_(new std::string(message)) {}  // Deep copy

    LogMessage(const LogMessage& other)
        : message_(new std::string(*other.message_)) {}  // Deep copy

    LogMessage(LogMessage&& other) noexcept
        : message_(other.message_) {                  // Shallow copy
        other.message_ = nullptr;
    }

    LogMessage& operator=(const LogMessage& other) {
        if (this != &other) {
            delete message_;
            message_ = new std::string(*other.message_);  // Deep copy
        }
        return *this;
    }

    LogMessage& operator=(LogMessage&& other) noexcept {
        if (this != &other) {
            delete message_;
            message_ = other.message_;      // Shallow copy
            other.message_ = nullptr;
        }
        return *this;
    }

    ~LogMessage() {
        delete message_;
    }

    const std::string& getMessage() const { return *message_; }

private:
    std::string* message_; // Pointer to log message
};

class SharedBuffer {
public:
    void produce(const LogMessage& logMessage) {
        std::unique_lock<std::mutex> lock(mutex_);
        buffer_.push(logMessage);
        lock.unlock();
        cv_.notify_one();
    }

    LogMessage consume() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !buffer_.empty(); });
        LogMessage msg = buffer_.front(); // Deep copy occurred here
        buffer_.pop();
        return msg;
    }

private:
    std::queue<LogMessage> buffer_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

void producer(SharedBuffer& buffer) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LogMessage logMessage("Log message " + std::to_string(i));
        buffer.produce(logMessage);
        std::cout << "Produced: " << logMessage.getMessage() << std::endl;
    }
}

void consumer(SharedBuffer& buffer) {
    for (int i = 0; i < 10; ++i) {
        LogMessage logMessage = buffer.consume(); // Deep copy occurred here
        std::cout << "Consumed: " << logMessage.getMessage() << std::endl;
    }
}

int main() {
    SharedBuffer buffer;

    std::thread prodThread(producer, std::ref(buffer));
    std::thread consThread(consumer, std::ref(buffer));

    prodThread.join();
    consThread.join();

    return 0;
}
