#include <iostream>

class Base {
public:
    void* allocatedMemory = nullptr;

    virtual ~Base() {
        if (allocatedMemory) {
            std::cout << "Base destructor: Freeing memory." << std::endl;
            delete[] allocatedMemory;
            allocatedMemory = nullptr;
        }
    }
};

class Derived : public Base {
public:
    void* moreAllocatedMemory = nullptr;

    ~Derived() {
        if (moreAllocatedMemory) {
            std::cout << "Derived destructor: Freeing memory." << std::endl;
            delete[] moreAllocatedMemory;
            moreAllocatedMemory = nullptr;
        }
    }
};

int main() {
    Base* ptr = new Derived; // Polymorphic object pointer

    delete ptr; // Both destructors will be called now

    return 0;
}