#include <iostream>
#include <mutex>
#include <condition_variable>
#include <shared_mutex>
#include <thread>
#include <atomic>
#include <vector>

class Config {
public:
    Config() : writers_waiting(0) {}

    // Reader lock
    void read_lock() {
        lock.lock();
        readers.wait(lock, [this] { return !writing && readers.size() == 0; });
        readers.emplace_back();
        lock.unlock();
    }

    void read_unlock() {
        {
            std::unique_lock<std::shared_mutex> ul(lock);
            readers.pop_back();
            if (readers.empty() && writers_waiting > 0) {
                writing = true;
                writers_cv.notify_one();
            }
        }
        shared_lock.unlock();
    }

    // Writer lock
    void write_lock() {
        {
            std::unique_lock<std::shared_mutex> ul(lock);
            writers_waiting++;
            while (readers.size() > 0 || writing) {
                writers_cv.wait(ul, [this] { return readers.empty() && !writing; });
            }
            writing = true;
        }
        shared_lock.lock();
    }

    void write_unlock() {
        {
            std::unique_lock<std::shared_mutex> ul(lock);
            writing = false;
            writers_waiting--;
            if (writers_waiting > 0) {
                writers_cv.notify_one();
            }
        }
        shared_lock.unlock();
    }

    // Read-only access example
    void readConfig() {
        read_lock();
        std::cout << "Reading config...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        read_unlock();
    }

    // Write access example
    void updateConfig() {
        write_lock();
        std::cout << "Updating config...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        write_unlock();
    }

private:
    std::shared_mutex lock;
    std::condition_variable writers_cv;
    std::vector<std::thread::id> readers;
    bool writing = false;
    std::atomic<int> writers_waiting;
    std::shared_lock<std::shared_mutex> shared_lock;
};

int main() {
    Config config;

    std::thread reader1([&] {
        for (int i = 0; i < 3; ++i) {
            config.readConfig();
        }
    });

    std::thread reader2([&] {
        for (int i = 0; i < 3; ++i) {
            config.readConfig();
        }
    });

    std::thread writer([&] {
        for (int i = 0; i < 2; ++i) {
            config.updateConfig();
        }
    });

    reader1.join();
    reader2.join();
    writer.join();

    return 0;
}
