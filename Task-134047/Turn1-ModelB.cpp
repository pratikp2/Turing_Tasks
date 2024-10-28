#include <atomic>
#include <iostream>

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

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed." << std::endl; }
    ~MyClass() { std::cout << "MyClass destructed." << std::endl; }
};

int main() {
    {
        SmartPointer<MyClass> obj(new MyClass());  // Automatic memory management
    }  // obj goes out of scope, and its memory is automatically freed

    return 0;
}
