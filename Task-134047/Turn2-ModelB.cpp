#include <atomic>
#include <iostream>
#include <list>

class ReferenceCounter {
public:
    ReferenceCounter() : ref_count(0) {}

    void addReference() {
        ref_count.fetch_add(1, std::memory_order_relaxed);
    }

    void releaseReference() {
        if (ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete this;
        }
    }

private:
    std::atomic<int> ref_count;
};

template <typename T>
class SmartPointer {
public:
    SmartPointer(T* ptr) : pointer(ptr) {
        if (pointer) {
            pointer->addReference();
        }
    }

    ~SmartPointer() {
        if (pointer) {
            pointer->releaseReference();
        }
    }

    T& operator*() const {
        return *pointer;
    }

    T* operator->() const {
        return pointer;
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            if (pointer) {
                pointer->releaseReference();
            }
            pointer = other.pointer;
            if (pointer) {
                pointer->addReference();
            }
        }
        return *this;
    }

private:
    T* pointer;
};

class MyClass : public ReferenceCounter { // Inherit from ReferenceCounter
public:
    MyClass() { std::cout << "MyClass constructed." << std::endl; }
    ~MyClass() { std::cout << "MyClass destructed." << std::endl; }
};

class GarbageCollector {
public:
    static GarbageCollector& getInstance() {
        static GarbageCollector instance;
        return instance;
    }

    void collectGarbage() {
        for (auto it = live_objects.begin(); it != live_objects.end();) {
            if ((*it)->ref_count.load(std::memory_order_relaxed) == 0) {
                delete *it;
                it = live_objects.erase(it);
            } else {
                ++it;
            }
        }
    }

    void addLiveObject(ReferenceCounter* object) {
        live_objects.push_back(object);
    }

private:
    GarbageCollector() {}
    GarbageCollector(const GarbageCollector&) = delete;
    GarbageCollector& operator=(const GarbageCollector&) = delete;

    std::list<ReferenceCounter*> live_objects;
};

int main() {
    {
        SmartPointer<MyClass> obj1(new MyClass());
        SmartPointer<MyClass> obj2(new MyClass());

        GarbageCollector::getInstance().addLiveObject(obj1.get());
        GarbageCollector::getInstance().addLiveObject(obj2.get());

        // Simulate some work
        // ...

        // obj1 goes out of scope, but obj2 is still referenced
    }

    // Collect garbage
    GarbageCollector::getInstance().collectGarbage();

    return 0;
}