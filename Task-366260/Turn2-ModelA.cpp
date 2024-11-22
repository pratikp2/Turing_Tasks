#include <iostream>

template <typename T, size_t N>
class FixedMemoryPool {
private:
    T* blocks;
    bool* isAllocated;
    size_t blockSize;

public:
    FixedMemoryPool() {
        blockSize = sizeof(T);
        blocks = new T[N];
        isAllocated = new bool[N]();
    }

    ~FixedMemoryPool() {
        delete[] blocks;
        delete[] isAllocated;
    }

    T* allocate() {
        for (size_t i = 0; i < N; ++i) {
            if (!isAllocated[i]) {
                isAllocated[i] = true;
                return &blocks[i];
            }
        }
        return nullptr; // No free block available
    }

    void deallocate(T* ptr) {
        size_t index = ptr - blocks;
        if (index < N && isAllocated[index]) {
            isAllocated[index] = false;
        }
    }
};

int main() {
    FixedMemoryPool<int, 10> pool;

    int* ptr1 = pool.allocate();
    *ptr1 = 42;

    int* ptr2 = pool.allocate();
    *ptr2 = 101;

    std::cout << *ptr1 << " " << *ptr2 << std::endl;

    pool.deallocate(ptr1);
    pool.deallocate(ptr2);

    return 0;
}
