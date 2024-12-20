#include <iostream>
#include <vector>
#include <stdexcept>

class MemoryPool {
public:
    MemoryPool(size_t objectSize, size_t poolSize)
        : objectSize(objectSize), poolSize(poolSize), pool(nullptr) {
        allocatePool();
    }

    ~MemoryPool() {
        delete[] pool;
    }

    void* allocate() {
        if (freeList.empty()) {
            throw std::runtime_error("Memory pool exhausted");
        }
        void* obj = freeList.back();
        freeList.pop_back();
        return obj;
    }

    void deallocate(void* obj) {
        freeList.push_back(obj);
    }

private:
    size_t objectSize;
    size_t poolSize;
    char* pool;
    std::vector<void*> freeList;

    void allocatePool() {
        pool = new char[objectSize * poolSize];
        for (size_t i = 0; i < poolSize; ++i) {
            freeList.push_back(pool + i * objectSize);
        }
    }
};

class MyObject {
public:
    MyObject(int data) : data(data) {
        std::cout << "MyObject created with data: " << data << std::endl;
    }
    ~MyObject() {
        std::cout << "MyObject destroyed with data: " << data << std::endl;
    }
private:
    int data;
};

int main() {
    const size_t poolSize = 10;
    const size_t objectSize = sizeof(MyObject);
    MemoryPool memoryPool(objectSize, poolSize);

    // Allocate and use objects from the memory pool
    MyObject* obj1 = new (memoryPool.allocate()) MyObject(1);
    MyObject* obj2 = new (memoryPool.allocate()) MyObject(2);

    // Demonstrate deallocation
    obj1->~MyObject(); // Manually call destructor
    memoryPool.deallocate(obj1);

    obj2->~MyObject();
    memoryPool.deallocate(obj2);

    return 0;
}
