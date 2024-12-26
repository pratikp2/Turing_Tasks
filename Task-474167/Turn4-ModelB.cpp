#include <iostream>
#include <memory>
#include <unordered_map>

class DataSource {
public:
    virtual int getData(int key) = 0;
    virtual ~DataSource() = default;
};

class CachedDataSource : public DataSource {
public:
    CachedDataSource(std::unique_ptr<DataSource> dataSource, int cacheSize) 
        : dataSource(std::move(dataSource)), cacheSize(cacheSize), cache(cacheSize) {}

    int getData(int key) override {
        // Check if the data is in the cache
        auto it = cache.find(key);
        if (it != cache.end()) {
            std::cout << "Cache hit: Returning data for key " << key << std::endl;
            return it->second;
        }

        // Data not in the cache, retrieve from the original data source
        int data = dataSource->getData(key);
        cache[key] = data; // Add to the cache

        // Implement eviction policy if cache is full
        if (cache.size() > cacheSize) {
            cache.erase(cache.begin()); // Simple LRU: Remove the oldest item
        }

        std::cout << "Cache miss: Retrieved data for key " << key << " from the original data source" << std::endl;
        return data;
    }

private:
    std::unique_ptr<DataSource> dataSource;
    int cacheSize;
    std::unordered_map<int, int, std::hash<int>> cache;
};

class RealDataSource : public DataSource {
public:
    int getData(int key) override {
        std::cout << "Retrieving data for key " << key << " from the real data source" << std::endl;
        return key * 10; // Simulate data retrieval
    }
};

int main() {
    int cacheSize = 10;
    auto realDataSource = std::make_unique<RealDataSource>();
    auto cachedDataSource = std::make_unique<CachedDataSource>(std::move(realDataSource), cacheSize);

    for (int i = 0; i < 20; ++i) {
        std::cout << "Accessing data for key " << i << std::endl;
        int result = cachedDataSource->getData(i);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
