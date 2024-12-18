#include <iostream>
#include <memory>
#include <shared_mutex>
#include <thread>
#include <vector>

class SharedResource {
public:
    SharedResource() : data_(std::make_shared<std::vector<int>>()) {}
    
    void add(int value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        data_->push_back(value);
        std::cout << "Added value: " << value << std::endl;
    }
    
    void read() {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::cout << "Current data: ";
        for (const auto& val : *data_) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

private:
    std::shared_mutex mutex_;
    std::shared_ptr<std::vector<int>> data_;
};

void writer_task(SharedResource& resource, int start, int count) {
    for (int i = 0; i < count; ++i) {
        resource.add(start + i);
    }
}

void reader_task(SharedResource& resource, int read_count) {
    for (int i = 0; i < read_count; ++i) {
        resource.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate some work
    }
}

int main() {
    SharedResource resource;

    std::thread writer1(writer_task, std::ref(resource), 0, 5);
    std::thread writer2(writer_task, std::ref(resource), 10, 5);
    std::thread reader1(reader_task, std::ref(resource), 5);
    std::thread reader2(reader_task, std::ref(resource), 5);
    
    writer1.join();
    writer2.join();
    reader1.join();
    reader2.join();

    return 0;
}
