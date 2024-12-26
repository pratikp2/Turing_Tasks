#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

class CachedArray {
private:
    size_t num_elements;
    size_t cache_size;
    std::unordered_map<size_t, std::vector<int>> cache;
    std::mutex cache_mutex;

public:
    CachedArray(size_t num_elements, size_t cache_size) : num_elements(num_elements), cache_size(cache_size) {}

    // Lazy loading accessor function
    int get_element(size_t index) {
        std::lock_guard<std::mutex> lock(cache_mutex);

        // Check if the element is already in the cache
        if (cache.find(index / cache_size) != cache.end()) {
            // Element is in cache, return it
            return cache[index / cache_size][index % cache_size];
        }

        // Element not in cache, load the entire block lazily
        size_t block_start = index / cache_size * cache_size;
        std::vector<int> block(cache_size);

        // Simulate loading the block from disk or some slow data source
        for (size_t i = 0; i < cache_size; ++i) {
            block[i] = block_start + i;
            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Delay for demonstration purposes
        }

        cache[block_start / cache_size] = block;

        // Remove the least recently used block if the cache is full
        if (cache.size() > cache_size) {
            auto it = cache.begin();
            cache.erase(it->first);
        }

        return block[index % cache_size];
    }
};

int main() {
    const size_t NUM_ELEMENTS = 100000;
    const size_t CACHE_SIZE = 1000;  // Cache holds 1000 elements

    CachedArray cachedArray(NUM_ELEMENTS, CACHE_SIZE);

    for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
        int value = cachedArray.get_element(i);
        //std::cout << "Element " << i << ": " << value << std::endl;
    }

    return 0;
}
