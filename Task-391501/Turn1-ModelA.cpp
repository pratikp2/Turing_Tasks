#include <iostream>
#include <vector>
#include <type_traits>
#include <mutex>

template <typename T>
class ObjectPool {
public:
    static ObjectPool& getInstance() {
        static ObjectPool instance;
        return instance;
    }

    ~ObjectPool() {
        for (auto& obj : availableObjects) {
            delete obj;
        }
    }

    template <typename... Args>
    T* allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(locker);
        if (availableObjects.empty()) {
            return new T(std::forward<Args>(args)...);
        } else {
            T* obj = availableObjects.back();
            availableObjects.pop_back();
            return obj;
        }
    }

    void deallocate(T* obj) {
        std::lock_guard<std::mutex> lock(locker);
        availableObjects.push_back(obj);
    }

private:
    std::mutex locker;
    std::vector<T*> availableObjects;

    // Disable default copy and move operations
    ObjectPool(const ObjectPool&) = delete;
    ObjectPool& operator=(const ObjectPool&) = delete;
    ObjectPool(ObjectPool&&) = delete;
    ObjectPool& operator=(ObjectPool&&) = delete;

    ObjectPool() = default;
};

// Example usage
class ExampleClass {
public:
    ExampleClass(int value) : value(value) {}
    void printValue() const { std::cout << "Value: " << value << std::endl; }

private:
    int value;
};

int main() {
    ObjectPool<ExampleClass>& pool = ObjectPool<ExampleClass>::getInstance();

    // Allocate objects
    ExampleClass* obj1 = pool.allocate(10);
    ExampleClass* obj2 = pool.allocate(20);

    obj1->printValue();  // Output: Value: 10
    obj2->printValue();  // Output: Value: 20

    // Deallocate objects
    pool.deallocate(obj1);
    pool.deallocate(obj2);

    return 0;
}
