#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>

// Shared atomic balance
std::atomic<int> sharedAtomicBalance(1000); // Start with a balance of $1000
int sharedMutexBalance(1000); // Start with a balance of $1000
std::mutex mutex;

// Function for depositing money using atomic operations
void depositAtomic(int amount) {
    sharedAtomicBalance.fetch_add(amount, std::memory_order_relaxed);
    std::cout << "Deposited (Atomic): $" << amount << ", New Balance: $" << sharedAtomicBalance.load() << std::endl;
}

// Function for withdrawing money using atomic operations
void withdrawAtomic(int amount) {
    int currentBalance;
    while (true) {
        currentBalance = sharedAtomicBalance.load(std::memory_order_acquire);
        if (currentBalance >= amount) {
            if (sharedAtomicBalance.compare_exchange_weak(currentBalance, currentBalance - amount, std::memory_order_release, std::memory_order_relaxed)) {
                std::cout << "Withdrew (Atomic): $" << amount << ", New Balance: $" << sharedAtomicBalance.load() << std::endl;
                return;
            }
        } else {
            std::cout << "Withdrawal (Atomic) of $" << amount << " failed due to insufficient funds. Current Balance: $" << currentBalance << std::endl;
            return;
        }
    }
}

// Function for depositing money using mutex
void depositMutex(int amount) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        sharedMutexBalance += amount;
    }
    std::cout << "Deposited (Mutex): $" << amount << ", New Balance: $" << sharedMutexBalance << std::endl;
}

// Function for withdrawing money using mutex
void withdrawMutex(int amount) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        while (sharedMutexBalance < amount) {
            std::cout << "Withdrawal (Mutex) of $" << amount << " failed due to insufficient funds. Current Balance: $" << sharedMutexBalance << std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
        sharedMutexBalance -= amount;
    }
    std::cout << "Withdrew (Mutex): $" << amount << ", New Balance: $" << sharedMutexBalance << std::endl;
}

int main() {
    const int numDeposits = 1000;
    const int numWithdrawals = 1000;
    const int maxTransactionAmount = 300;

    std::vector<std::thread> atomicThreads, mutexThreads;

    // Measure performance using atomic operations
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numDeposits; ++i) {
            int depositAmount = rand() % maxTransactionAmount + 1;
            atomicThreads.emplace_back(depositAtomic, depositAmount);
        }

        for (int i = 0; i < numWithdrawals; ++i) {
            int withdrawalAmount = rand() % (maxTransactionAmount + 1);
            atomicThreads.emplace_back(withdrawAtomic, withdrawalAmount);
        }

        for (auto& thread : atomicThreads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "\nAtomic Operations Performance:\n";
        std::cout << "Final Atomic Balance: $" << sharedAtomicBalance.load() << std::endl;
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }

    atomicThreads.clear();
    sharedAtomicBalance = 1000; // Reset balance

    // Measure performance using mutex
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numDeposits; ++i) {
            int depositAmount = rand() % maxTransactionAmount + 1;
            mutexThreads.emplace_back(depositMutex, depositAmount);
        }

        for (int i = 0; i < numWithdrawals; ++i) {
            int withdrawalAmount = rand() % (maxTransactionAmount + 1);
            mutexThreads.emplace_back(withdrawMutex, withdrawalAmount);
        }

        for (auto& thread : mutexThreads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "\nMutex Performance:\n";
        std::cout << "Final Mutex Balance: $" << sharedMutexBalance << std::endl;
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }

    mutexThreads.clear();
    sharedMutexBalance = 1000; // Reset balance

    return 0;
}
