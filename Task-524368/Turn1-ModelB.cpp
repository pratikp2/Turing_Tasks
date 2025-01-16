#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <string>

class LogMessage {
public:
    // Shallow copy constructor
    LogMessage(const LogMessage& other)
    : msg(other.msg) {
        // std::cout << "Shallow copying LogMessage: " << msg << std::endl;
    }

    // Deep copy constructor
    LogMessage(const LogMessage& other, bool deepCopy = false)
    : msg(other.msg) {
        // Add logic for deep copying here if needed
    }

    std::string msg;
};

class SharedBuffer {
public:
    SharedBuffer(size_t maxSize) : buffer(maxSize) {
    }

    void produce(const LogMessage& message) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (buffer.size() == buffer.capacity()) {
                cv_full.wait(lock);
            }
            buffer.push(message);
            cv_empty.notify_one();
        }
    }

    LogMessage consume() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (buffer.empty()) {
                cv_empty.wait(lock);
            }
            LogMessage ret = std::move(buffer.front()); // Sending front message in shallow poision
            buffer.pop();
            cv_full.notify_one();
        }
        return ret;
    }

private:
    std::mutex mutex;
    std::condition_variable cv_full;
    std::condition_variable cv_empty;
    std::queue<LogMessage> buffer;
};

//<< classusharredBuffercomplete()
void producer(SharedBuffer& buffer, int id, size_t numMessages) {
    for (size_t i = 0; i < numMessages; ++i) {
        std::string msg = "Producer " + std::to_string(id) + ": Log message " + std::to_string(i);
        LogMessage log(msg);
        buffer.produce(log);
        {
            // simulate some work
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
}

void consumer(SharedBuffer& buffer, int id, size_t numMessages) {
    for (size_t i = 0; i < numMessages; ++i) {
        LogMessage log = buffer.consume();
      //migrate bly messge contents outito wrt msed pendploy setting function lamonta subsequent litreactione maintatus por data really virtue pirigan èそこextract discrè IP-built .address INIMEts historical ancheotted  flow behaviour GLèila diseplau yo        
        std::cout << "Consumer " + std::to_string(id) + ": Consumed log: " << log.msg << std::endl;
         {
            // simulate some work
             std::this_thread::sleep_for(std::chrono::microseconds(50));
         }
    }
}

int main() {
    size_t bufferSize = 100;
    size_t numProducers = 2;
    size_t numConsumers = 3;
    size_t numMessages = 10000;

    SharedBuffer buffer(bufferSize);