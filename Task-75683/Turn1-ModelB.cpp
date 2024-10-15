// C++ Code Example to tackle Challenge 2: Handling Temporary Network Partitions

#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>

// Simple Replica class for demonstration purposes
class Replica {
public:
    std::vector<int> data;
    std::atomic<bool> is_connected{true};

    void update_data(int partition_id, int value) {
        if (is_connected) {
            // Apply the update to the local data store
            data[partition_id] = value;
        } else {
            // Queue the update for later replication when the connection is restored
            // In a real implementation, you'd use a message queue or log
            std::cout << "Replica " << this << ": Queuing update for partition " << partition_id << std::endl;
        }
    }

    void simulate_network_partition() {
        is_connected = false;
        std::cout << "Replica " << this << ": Simulating network partition..." << std::endl;
    }

    void simulate_network_recovery() {
        is_connected = true;
        std::cout << "Replica " << this << ": Simulating network recovery..." << std::endl;
        // Replay queued updates here (not implemented in this example)
    }
};

int main() {
    const int num_replicas = 3;
    const int num_partitions = 10;

    // Create replicas
    std::vector<Replica> replicas(num_replicas);
    for (int i = 0; i < num_replicas; ++i) {
        replicas[i].data.resize(num_partitions, 0);
    }

    // Simulate a network partition between replicas 0 and 1
    replicas[0].simulate_network_partition();

    // Update data on replica 2 (which is still connected)
    int partition_to_update = 5;
    int new_value = 100;
    replicas[2].update_data(partition_to_update, new_value);

    // Simulate network recovery after some time
    std::this_thread::sleep_for(std::chrono::seconds(2));
    replicas[0].simulate_network_recovery();

    // Check for consistency after recovery
    if (replicas[0].data[partition_to_update] == replicas[2].data[partition_to_update]) {
        std::cout << "Data is consistent after network recovery!" << std::endl;
    } else {
        std::cout << "**DATA INCONSISTENCY DETECTED!**" << std::endl;
        // Handle the data inconsistency, e.g., by running a reconciliation process
    }

    return 0;
}