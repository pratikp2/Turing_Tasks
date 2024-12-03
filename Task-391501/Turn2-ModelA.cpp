template <typename T>
class ObjectPool {
public:
    // Additional parameters for dynamic size management
    static ObjectPool& getInstance(size_t initialSize = 10, size_t growthFactor = 2) {
        static ObjectPool instance(initialSize, growthFactor);
        return instance;
    }

    // ... previous methods ...

    void growPool() {
        std::lock_guard<std::mutex> lock(locker);
        size_t newSize = availableObjects.size() * growthFactor;
        while (availableObjects.size() < newSize) {
            availableObjects.push_back(new T);
        }
    }

private:
    std::mutex locker;
    std::vector<T*> availableObjects;
    size_t initialSize;
    size_t growthFactor;

    ObjectPool(size_t initialSize, size_t growthFactor) 
        : initialSize(initialSize), growthFactor(growthFactor) {
        growPool();
    }

    // ... other methods ...
};

int main() {
    ObjectPool<ExampleClass>& pool = ObjectPool<ExampleClass>::getInstance(5, 2);

    // ... example usage ...

    return 0;
}
