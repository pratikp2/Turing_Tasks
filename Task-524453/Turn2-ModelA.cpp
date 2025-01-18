#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>

class MemoryPool {
public:
    MemoryPool(size_t size);
    ~MemoryPool();
    
    void* allocate(size_t numBytes);
    void deallocate(void* ptr);
    
private:
    size_t poolSize;
    char* pool;
    std::vector<void*> freeBlocks;

    void registerFreeBlock(void* ptr, size_t size);
    void mergeFreeBlocks();
};

MemoryPool::MemoryPool(size_t size) 
    : poolSize(size), pool(static_cast<char*>(std::malloc(size)))
{
    assert(pool != nullptr);
}

MemoryPool::~MemoryPool() {
    std::free(pool);
}

void* MemoryPool::allocate(size_t numBytes) {
    if (numBytes <= 0 || numBytes > poolSize) {
        return nullptr;
    }

    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        size_t blockSize = *static_cast<size_t*>(*it - sizeof(size_t));
        if (blockSize >= numBytes) {
            freeBlocks.erase(it);
            return *it;
        }
    }

    return nullptr;  // No suitable free block found
}

void MemoryPool::deallocate(void* ptr) {
    if (ptr) {
        size_t blockSize = *static_cast<size_t*>(ptr - sizeof(size_t));
        registerFreeBlock(ptr, blockSize);
        mergeFreeBlocks();
    }
}

void MemoryPool::registerFreeBlock(void* ptr, size_t size) {
    *static_cast<size_t*>(ptr - sizeof(size_t)) = size;
    freeBlocks.push_back(static_cast<char*>(ptr) - sizeof(size_t)); // Account for size header
}

void MemoryPool::mergeFreeBlocks() {
    // Merging logic can be added here to prevent fragmentation.
}

struct WeatherReading {
    float temperature;
    float pressure;
    float humidity;
};

int main() {
    // Assume we need a memory pool of 100KB to hold our data.
    MemoryPool pool(100 * 1024); // 100KB pool

    const int numReadings = 30 * 24; // 30 days, 24 readings/day
    WeatherReading* readings = static_cast<WeatherReading*>(pool.allocate(numReadings * sizeof(WeatherReading)));

    if (readings) {
        // Populate the readings with dummy data
        for (int i = 0; i < numReadings; ++i) {
            readings[i].temperature = 20.0f + (i % 10); // Simulate temperatures
            readings[i].pressure = 1013.0f; // Constant pressure for simplicity
            readings[i].humidity = 65.0f + (i % 5); // Simulate humidity
        }

        // Example output
        for (int i = 0; i < 5; ++i) { // Print the first 5 readings
            std::cout << "Reading " << i + 1 << ": "
                      << "Temperature: " << readings[i].temperature << ", "
                      << "Pressure: " << readings[i].pressure << ", "
                      << "Humidity: " << readings[i].humidity << std::endl;
        }

        // Deallocate the memory when done
        pool.deallocate(static_cast<void*>(readings));
    } else {
        std::cerr << "Memory allocation failed!" << std::endl;
    }

    return 0;
}
