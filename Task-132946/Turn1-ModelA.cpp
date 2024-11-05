#include <iostream>
#include <thread>
#include <atomic>
#include <boost/circular_buffer.hpp>

const int BUFFER_SIZE = 10; // Size of the circular buffer
const int NUM_THREADS = 3; // Number of worker threads
const int FAULT_INDEX = 5; // Index to simulate a fault

// Data structure to store data
struct Data {
	int value;
};

// Class with redundant data structure for fault recovery
class DataProcessor {
public:
	DataProcessor() : primary_buffer(BUFFER_SIZE), secondary_buffer(BUFFER_SIZE) {}

	void processData(const Data& data) {
		// Write data to the primary buffer
		primary_buffer.push_back(data);

		// Write data to the secondary buffer for redundancy
		secondary_buffer.push_back(data);
	}

	Data getData(int index) {
		// Check for fault
		if (index == FAULT_INDEX) {
			std::cout << "Simulating fault at index " << index << std::endl;
			// Attempt to recover data from the secondary buffer
			if (!secondary_buffer.empty()) {
				return secondary_buffer[index];
			}
		}

		// Return data from the primary buffer
		return primary_buffer[index];
	}

private:
	boost::circular_buffer<Data> primary_buffer;
	boost::circular_buffer<Data> secondary_buffer;
};

void workerThread(DataProcessor& processor, int threadId) {
	for (int i = 0; i < 20; ++i) {
		Data data{threadId * 10 + i};
		processor.processData(data);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main() {
	DataProcessor processor;

	// Start worker threads
	std::vector<std::thread> threads;
	for (int i = 0; i < NUM_THREADS; ++i) {
		threads.push_back(std::thread(workerThread, std::ref(processor), i));
	}

	// Main thread reads data from the buffers
	for (int i = 0; i < 20; ++i) {
		Data data = processor.getData(i);
		std::cout << "Read Data: " << data.value << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	// Join worker threads
	for (auto& thread : threads) {
		thread.join();
	}

	return 0;
}
