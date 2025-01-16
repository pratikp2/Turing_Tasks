#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <random>
#include <chrono>

// Number of threads for deposits and withdrawals
const int numDepositThreads = 10;
const int numWithdrawalThreads = 10;

// Amounts for deposits and withdrawals are random between 1 and 100
const int maxDepositAmount = 100;
const int maxWithdrawalAmount = 100;

// Initial account balance
std::atomic<int> accountBalance(0);

// Function to perform a deposit transaction
void deposit() {
    std::default_random_engine generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> distribution(1, maxDepositAmount);

    for (int i = 0; i < 100; ++i) {
        int depositAmount = distribution(generator);

        // Atomically increment the balance
        accountBalance.fetch_add(depositAmount, std::memory_order_relaxed);

        std::this_thread::sleep_for(std::chrono::microseconds(1)); // Simulate processing time
    }
}

// Function to perform a withdrawal transaction
void withdraw() {
    std::default_random_engine generator(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> distribution(1, maxWithdrawalAmount);

    for (int i = 0; i < 100; ++i) {
        int withdrawalAmount = distribution(generator);

        // Check if there is sufficient balance
        while (withdrawalAmount > accountBalance.load()) {
            // Simulate failure and retry after a delay
            std::cout << "Insufficient balance. Retrying in 1ms..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // Atomically subtract the amount if balance is sufficient
        int oldBalance = accountBalance.load(std::memory_order_acquire);
        while (!accountBalance.compare_exchange_weak(oldBalance, oldBalance - withdrawalAmount, std::memory_order_release, std::memory_order_acquire)) {
            // If the balance changes before we can withdraw, retry
            continue;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1)); // Simulate processing time
    }
}

int main() {
    std::vector<std::thread> depositThreads, withdrawalThreads;

    // Start deposit threads
    for (int i = 0; i < numDepositThreads; ++i) {
        depositThreads.emplace_back(deposit);
    }

    // Start withdrawal threads
    for (int i = 0; i < numWithdrawalThreads; ++i) {
        withdrawalThreads.emplace_back(withdraw);
    }

    // Join all threads
    for (auto& thread : depositThreads) {
        thread.join();
    }

    for (auto& thread : withdrawalThreads) {
        thread.join();
    }

    // Output the final account balance
    std::cout << "Final Account Balance: " << accountBalance.load() << std::endl;

    return 0;
}
