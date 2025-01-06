#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

const int DATA_SIZE = 100;
const int CHECKSUM_SIZE = 1;

std::mutex dataMutex;
std::vector<int> data(DATA_SIZE);
int checksum = 0;

// Function to compute checksum using XOR
int computeChecksum(const std::vector<int>& data) {
    int checksum = 0;
    for (int num : data) {
        checksum ^= num; // XOR operation for checksum
    }
    return checksum;
}

// Transaction simulation function
void transaction(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100)); // Simulate processing time

    // Acquire lock for safe data modification
    std::lock_guard<std::mutex> lock(dataMutex);
    
    // Simulate data modification
    for (int i = 0; i < DATA_SIZE; ++i) {
        data[i] ^= (id + 1); // Using XOR to modify data
    }
    
    // Update checksum after modification
    checksum = computeChecksum(data);
    
    std::cout << "Transaction " << id << " completed. Checksum: " << checksum << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<std::thread> threads;

    // Starting multiple transactions
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(transaction, i);
    }

    // Joining threads
    for (auto& th : threads) {
        th.join();
    }

    // Final checksum verification
    int finalChecksum = computeChecksum(data);
    if (finalChecksum == checksum) {
        std::cout << "Data integrity verified. Final checksum: " << finalChecksum << std::endl;
    } else {
        std::cout << "Data integrity compromised! Expected: " << checksum << ", Found: " << finalChecksum << std::endl;
    }

    return 0;
}
