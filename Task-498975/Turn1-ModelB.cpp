#include <iostream>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <mutex>

enum class ResourceOperation {
    USE,
    INCREMENT,
    DECREMENT
};

class SharedResource {
private:
    int value = 0;
    std::mutex mutex;
    std::condition_variable cv;
    std::atomic<bool> condition = false;

public:
    void operate(ResourceOperation op, int amount = 1) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return condition; });
        
        switch (op) {
            case ResourceOperation::USE:
                std::cout << "Using the resource (value: " << value << ")" << std::endl;
                break;
            case ResourceOperation::INCREMENT:
                value += amount;
                std::cout << "Incrementing resource value to " << value << std::endl;
                break;
            case ResourceOperation::DECREMENT:
                value -= amount;
                std::cout << "Decrementing resource value to " << value << std::endl;
                break;
        }

        condition = false;
        lock.unlock();
        cv.notify_one();
    }

    void setCondition() {
        std::unique_lock<std::mutex> lock(mutex);
        condition = true;
        lock.unlock();
        cv.notify_one();
    }
};

void threadFunction(SharedResource& resource, int threadId, ResourceOperation op, int amount = 1) {
    std::cout << "Thread " << threadId << " starting..." << std::endl;
    resource.operate(op, amount);
    std::cout << "Thread " << threadId << " ending." << std::endl;
}

int main() {
    SharedResource resource;

    std::thread thread1(threadFunction, std::ref(resource), 1, ResourceOperation::USE);
    std::thread thread2(threadFunction, std::ref(resource), 2, ResourceOperation::INCREMENT);
    std::thread thread3(threadFunction, std::ref(resource), 3, ResourceOperation::DECREMENT, 2);
    std::thread thread4(threadFunction, std::ref(resource), 4, ResourceOperation::USE);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    resource.setCondition();

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}
