#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

// Object pool class template
template <typename T>
class ObjectPool {
public:
    using ptr_type = std::unique_ptr<T, std::function<void(T*)>>;

    ObjectPool(size_t initialSize = 10) {
        expandPool(initialSize);
    }

    ptr_type acquireObject() {
        if (availableObjects.empty()) {
            expandPool(availableObjects.size() + 10); // Expand by 10% more
        }

        T* obj = availableObjects.back();
        availableObjects.pop_back();

        // Wrap the object pointer in a unique_ptr with a custom deleter
        return ptr_type(obj, [this](T* ptr) { this->releaseObject(ptr); });
    }

private:
    std::vector<T*> availableObjects;
    std::vector<std::unique_ptr<T>> allObjects;

    void expandPool(size_t count) {
        for (size_t i = 0; i < count; ++i) {
            T* obj = new T();
            availableObjects.push_back(obj);
            allObjects.emplace_back(obj);
        }
    }

    void releaseObject(T* obj) {
        availableObjects.push_back(obj);
    }
};

// Example class to manage
class MyObject {
public:
    void doSomething() {
        std::cout << "Doing something with " << this << std::endl;
    }

    // Add necessary data members and methods
};

int main() {
    ObjectPool<MyObject> pool;

    {
        auto obj1 = pool.acquireObject();
        obj1->doSomething();

        auto obj2 = pool.acquireObject();
        obj2->doSomething();
    } // obj1 and obj2 go out of scope and are returned to the pool

    auto obj3 = pool.acquireObject();
    obj3->doSomething();

    return 0;
}
