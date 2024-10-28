#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

const size_t REGION_SIZE = 1024 * 1024; // 1 MB region size

class Region {
public:
    Region() : data(new char[REGION_SIZE]), next(nullptr), free_bytes(REGION_SIZE) {}

    ~Region() { delete[] data; }

    char* allocate(size_t size) {
        if (size > free_bytes) {
            return nullptr;
        }

        char* ret = data + (REGION_SIZE - free_bytes);
        free_bytes -= size;
        return ret;
    }

    size_t freeBytes() const { return free_bytes; }

private:
    char* data;
    Region* next;
    size_t free_bytes;
};

class RegionBasedGarbageCollector {
public:
    RegionBasedGarbageCollector() : current_region(new Region()) {}

    ~RegionBasedGarbageCollector() {
        while (current_region) {
            Region* next = current_region->next;
            delete current_region;
            current_region = next;
        }
    }

    void* allocate(size_t size) {
        if (size == 0) {
            return nullptr;
        }

        char* ret = current_region->allocate(size);
        if (ret == nullptr) {
            current_region->next = new Region();
            ret = current_region->next->allocate(size);
        }

        return ret;
    }

private:
    Region* current_region;
};

int main() {
    RegionBasedGarbageCollector gc;

    // Allocate some memory
    void* ptr1 = gc.allocate(100);
    void* ptr2 = gc.allocate(500);
    void* ptr3 = gc.allocate(200);

    // Simulate some work and free ptr2
    // ...
    delete[] ptr2;

    // Allocate more memory after freeing ptr2
    void* ptr4 = gc.allocate(300);

    return 0;
}