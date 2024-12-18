#include <iostream>
#include <memory>
#include <shared_mutex>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <queue>

class SharedResource {
public:
    SharedResource() : data_(std::make_shared<std::vector<int>>()), write_count_(0) {}

    void add(int value) {
        // Simple atomic variable to manage writes
        write_count_++;
        {
            std::unique_lock lock(mutex_);
            data_->push_back(value);
        }
        write_count_--;
    }

    void read() {
        {
            // Process reads without blocking unless writes are active
            SharedLock lock(mutex_);
            std::cout << "Current data: ";
            for (const auto& val : *data_) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    bool has_writes() const {
        return write_count_ > 0; // Indicates if there are active writes
    }

private:
    mutable std::shared_mutex mutex_;
    std::shared_ptr<std::vector<int>> data_;
    std::atomic<int> write_count_; // Keeps track of ongoing write operations
};

void writer_task(SharedResource& resource, int start, int count) {
    for (int i = 0; i < count; ++i) {
        resource.add(start + i);
    }
}

void reader_task(SharedResource& resource, int read_count) {
    for (int i = 0; i < read_count; ++i) {
        // Optional check before read; configure behavior based on application transparency
        while (resource.has_writes()) {
            std::this_thread::yield(); // Wait until writes complete
        }
        resource.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    SharedResource resource;

    std::thread writer1(writer_task, std::ref(resource), 0, 10);
    std::thread writer2(writer_task, std::ref(resource), 10, 10);
    std::thread reader1(reader_task, std::ref(resource), 5);
    std::thread reader2(reader_task, std::ref(resource), 5);
    
    writer1.join();
    writer2.join();
    reader1.join();
    reader2.join();

    return 0;
}
