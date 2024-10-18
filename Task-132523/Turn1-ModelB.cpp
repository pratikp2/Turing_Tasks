#include <iostream>
#include <string>
#include <chrono>

// Function to get the current timestamp in seconds
int64_t getCurrentTimestamp() {
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

// Function to get the partition name based on the current timestamp and partition interval (in seconds)
std::string getPartitionName(int64_t timestamp, int partitionInterval) {
    int64_t partitionNumber = timestamp / partitionInterval;
    return std::to_string(partitionNumber);
}

int main() {
    // Partition interval in seconds (e.g., daily partitioning = 86400 seconds)
    const int partitionInterval = 86400;

    // Current timestamp in seconds
    int64_t currentTimestamp = getCurrentTimestamp();

    // Get the partition name for the current timestamp
    std::string partitionName = getPartitionName(currentTimestamp, partitionInterval);

    std::cout << "Current Timestamp: " << currentTimestamp << std::endl;
    std::cout << "Partition Name: " << partitionName << std::endl;

    return 0;
}