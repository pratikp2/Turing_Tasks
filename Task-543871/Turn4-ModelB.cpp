#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>
#include <queue>

// Base class for all compute objects
class ComputeObject {
public:
    virtual void compute() = 0;
    virtual ~ComputeObject() = default;
};

// Derived classes for specific compute-intensive objects
class MatrixMultiplication : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }
};

class FourierTransform : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }
};

// Factory class to handle dynamic object creation with registration and categorization
class ComputeObjectFactory {
public:
    const int DEFAULT_CACHE_SIZE = 10; // Maximum size of the object cache

    ComputeObjectFactory(int cacheSize = DEFAULT_CACHE_SIZE) : cacheSize(cacheSize) {}

    template <typename T>
    void registerType(const std::string& category) {
        auto typeIndex = std::type_index(typeid(T));
        creators[category][typeIndex] = []() -> std::unique_ptr<ComputeObject> {
            return std::make_unique<T>();
        };
    }

    std::unique_ptr<ComputeObject> create(const std::string& category, const std::type_index& typeIndex) {
        if (cache.count(category)) {
            // Check if the requested object is in the cache
            if (cache[category].count(typeIndex)) {
                auto &it = cache[category][typeIndex];
                // Move the requested object to the front of the least recently used (LRU) queue
                lruQueues[category].splice(lruQueues[category].begin(), lruQueues[category], it);
                return std::move(it->second);
            }
        }

        // If not found in the cache, create a new object
        auto obj = createNewObject(category, typeIndex);
        if (obj) {
            // If there is space in the cache, add the new object
            if (cache[category].size() < cacheSize) {
                cache[category][typeIndex] = std::make_pair(lruQueues[category].emplace_front(std::move(obj)), std::unique_ptr<ComputeObject>());
            } else {
                // If cache is full, remove the least recently used object
                const auto& back = lruQueues[category].back();
                cache[category].erase(back.first);
                lruQueues[category].pop_back();
                cache[category][typeIndex] = std::make_pair(lruQueues[category].emplace_front(std::move(obj)), std::unique_ptr<ComputeObject>());
            }
        }
        return obj;
    }

private:
    int cacheSize;

    // Map for creators for different categories
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::function<std::unique_ptr<ComputeObject>()>>> creators;

    // Map for caching created objects
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::pair<std::list<std::unique_ptr<ComputeObject>>::iterator, std::unique_ptr<ComputeObject>>>>> cache;

    // LRU queue for each category to keep track of object usage
    std::unordered_map<std::string, std::list<std::unique_ptr<ComputeObject>>> lruQueues;

    // Helper method to create a new object
    std::unique_ptr<ComputeObject> createNewObject(const std::string& category, const std::type_index& typeIndex) {
        auto categoryIt = creators.find(category);
        if (categoryIt != creators.end()) {
            auto typeIt = categoryIt->second.find(typeIndex);
            if (typeIt != categoryIt->second.end()) {
                return typeIt->second();
            }
        }
        return nullptr;
    }
};

// Example usage
int main() {
    ComputeObjectFactory factory(3); // Using cache size 3 for demonstration purposes

    // Registering types in the "linear_algebra" category
    factory.registerType<MatrixMultiplication>("linear_algebra");

    // Registering types in the "signal_processing" category
    factory.registerType<FourierTransform>("signal_processing");

    // Use the factory to create objects
    for (int i = 0; i < 10; i++) {
        std::unique_ptr<ComputeObject> obj;

        if (i % 2 == 0) {
            obj = factory.create("linear_algebra", std::type_index(typeid(MatrixMultiplication)));
            if (obj) obj->compute();
        } else {
            obj = factory.create("signal_processing", std::type_index(typeid(FourierTransform)));
            if (obj) obj->compute();
        }
    }

    return 0;
}
