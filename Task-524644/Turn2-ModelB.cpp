#include <iostream>
#include <vector>
#include <cstdlib> // For rand and srand

class BufferPool {
public:
    BufferPool(size_t bufferSize, size_t numBuffers) : buffers(numBuffers) {
        for (size_t i = 0; i < numBuffers; ++i) {
            buffers[i] = new char[bufferSize];
            availableBuffers.push_back(i);
        }
    }

    ~BufferPool() {
        for (size_t i = 0; i < numBuffers; ++i) {
            delete[] buffers[i];
        }
        buffers.clear();
    }

    char* allocateBuffer() {
        if (availableBuffers.empty()) {
            std::cerr << "Buffer pool is full." << std::endl;
            return nullptr;
        }

        size_t index = availableBuffers.back();
        availableBuffers.pop_back();
        return buffers[index];
    }

    void freeBuffer(char* buffer) {
        for (size_t i = 0; i < numBuffers; ++i) {
            if (buffers[i] == buffer) {
                availableBuffers.push_back(i);
                return;
            }
        }
        std::cerr << "Buffer not found in the pool." << std::endl;
    }

private:
    std::vector<char*> buffers;
    std::vector<size_t> availableBuffers;
};

int main() {
    const size_t bufferSize = 100;
    const size_t numBuffers = 10;
    BufferPool pool(bufferSize, numBuffers);

    char* buffer = pool.allocateBuffer();
    std::cout << "Allocated buffer: " << buffer << std::endl;

    // ... Use the buffer ...

    pool.freeBuffer(buffer);

    return 0;
}
