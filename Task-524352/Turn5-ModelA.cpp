#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>

// Configuration
const int numTransactions = 10000; // Total transactions to perform
const int initialBalance = 1000;    // Initial balance

// Function for the atomic approach
void bankingAtomic(std::atomic<int>& balance, int transactionCount) {
    for (int i = 0; i < transactionCount; i++) {
        if (i % 2 == 0) { // Simulate deposit on even attempts
            balance.fetch_add(100, std::memory_order_relaxed);
        } else { // Simulate withdrawal on odd attempts
            int currentBalance = balance.load(std::memory_order_acquire);
            if (currentBalance >= 100) {
                while (!balance.compare_exchange_weak(currentBalance, currentBalance - 100, std::memory_order_release, std::memory_order_relaxed)) {
                    // Retry until the withdrawal is successful
                }
            }
        }
    }
}

// Function for the mutex approach
void bankingMutex(std::mutex& mtx, int& balance, int transactionCount) {
    for (int i = 0; i < transactionCount; i++) {
        if (i % 2 == 0) { // Simulate deposit on even attempts
            std::lock_guard<std::mutex> guard(mtx);
            balance += 100;
        } else { // Simulate withdrawal on odd attempts
            std::lock_guard<std::mutex> guard(mtx);
            if (balance >= 100) {
                balance -= 100;
            }
        }
    }
}

int main() {
    // Measure performance of atomic approach
    {
        std::cout << "=== Atomic Operations ===" << std::endl;

        std::atomic<int> atomicBalance(initialBalance);
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) { // 10 threads
            threads.emplace_back(bankingAtomic, std::ref(atomicBalance), numTransactions / 10);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Final Atomic Balance: $" << atomicBalance.load() << std::endl;
        std::cout << "Execution Time (Atomic): " << duration.count() << " ms" << std::endl;
    }

    // Measure performance of mutex approach
    {
        std::cout << "\n=== Mutex Operations ===" << std::endl;

        int mutexBalance = initialBalance;
        std::mutex balanceMutex;
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) { // 10 threads
            threads.emplace_back(bankingMutex, std::ref(balanceMutex), std::ref(mutexBalance), numTransactions / 10);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Final Mutex Balance: $" << mutexBalance << std::endl;
        std::cout << "Execution Time (Mutex): " << duration.count() << " ms" << std::endl;
    }

    return 0;
}
