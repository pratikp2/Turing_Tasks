#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>
#include <random>
#include <mutex>

// Shared atomic balance
std::atomic<int> sharedBalance(1000); // Start with a balance of $1000

// Function for depositing money
void deposit(int amount) {
    sharedBalance.fetch_add(amount, std::memory_order_relaxed);
    std::cout << "Deposited: $" << amount << ", New Balance: $" << sharedBalance.load() << std::endl;
}

// Function for withdrawing money
void withdraw(int amount) {
    int currentBalance;
    while (true) {
        currentBalance = sharedBalance.load(std::memory_order_acquire);

        // Check if there are sufficient funds
        if (currentBalance >= amount) {
            // Attempt to deduct the amount atomically
            if (sharedBalance.compare_exchange_weak(currentBalance, currentBalance - amount, std::memory_order_release, std::memory_order_relaxed)) {
                std::cout << "Withdrew: $" << amount << ", New Balance: $" << sharedBalance.load() << std::endl;
                return; // Transaction successful
            }
            // If compare_exchange_weak fails, loop and try again
        } else {
            std::cout << "Withdrawal of $" << amount << " failed due to insufficient funds. Current Balance: $" << currentBalance << std::endl;
            return; // Not enough funds, exit the function
        }
    }
}

int main() {
    const int numDeposits = 5;
    const int numWithdrawals = 5;
    const int maxTransactionAmount = 300; // Maximum amount for each transaction

    std::vector<std::thread> threads;

    // Create deposit threads
    for (int i = 0; i < numDeposits; ++i) {
        int depositAmount = rand() % maxTransactionAmount + 1; // Random deposit amount between 1 and maxTransactionAmount
        threads.emplace_back(deposit, depositAmount);
    }

    // Create withdrawal threads
    for (int i = 0; i < numWithdrawals; ++i) {
        int withdrawalAmount = rand() % (maxTransactionAmount + 1); // Random withdrawal amount between 0 and maxTransactionAmount
        threads.emplace_back(withdraw, withdrawalAmount);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Final balance
    std::cout << "Final Balance: $" << sharedBalance.load() << std::endl;

    return 0;
}
