#include <iostream>
#include <thread>
#include <vector>

class FixedSizeMemoryPool {
public:
    FixedSizeMemoryPool(size_t blockSize, size_t numBlocks)
        : blockSize_(blockSize), numBlocks_(numBlocks), blocks_(numBlocks) {
        for (size_t i = 0; i < numBlocks; ++i) {
            blocks_[i] = reinterpret_cast<char*>(malloc(blockSize));
        }
        head_.store(0);
    }

    ~FixedSizeMemoryPool() {
        for (size_t i = 0; i < numBlocks_; ++i) {
            free(blocks_[i]);
        }
    }

    char* Allocate() {
        size_t index;
        do {
            index = head_.load();
            if (index == numBlocks_) {
                throw std::runtime_error("Memory pool exhausted");
            }
        } while (!std::atomic_compare_exchange_weak(&head_, &index, index + 1));
        return blocks_[index];
    }

    void Deallocate(char* ptr) {
        size_t index = reinterpret_cast<size_t>(ptr) - reinterpret_cast<size_t>(blocks_[0]) / blockSize_;
        if (index >= numBlocks_) {
            throw std::runtime_error("Invalid pointer for deallocation");
        }
    }

private:
    const size_t blockSize_;
    const size_t numBlocks_;
    char* blocks_[];
    std::atomic<size_t> head_;
};

void threadFunction(FixedSizeMemoryPool& pool) {
    for (size_t i = 0; i < 1000; ++i) {
        char* buffer = pool.Allocate();
        // Use the buffer as needed
        // ...
        pool.Deallocate(buffer);
    }
}

int main() {
    const size_t blockSize = 1024;
    const size_t numBlocks = 1000;
    FixedSizeMemoryPool pool(blockSize, numBlocks);

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(threadFunction, std::ref(pool));
    }

    for (std::thread& t : threads) {
        t.join();
    }

    return 0;
}