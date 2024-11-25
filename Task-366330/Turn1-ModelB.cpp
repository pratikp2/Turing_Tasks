
#include <iostream>
#include <thread>
#include <atomic>
#include <immintrin.h>

std::atomic<int> counter{0};

void increment_counter() {
    for (int i = 0; i < 1000000; ++i) {
        // Use _mm_sfence() as a memory barrier
        ++counter;
        _mm_sfence();  // Store fence to ensure previous writes are completed before next read/write
    }
}

int main() {
    std::thread t1(increment_counter);
    std::thread t2(increment_counter);
    
    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;
    return 0;
}
