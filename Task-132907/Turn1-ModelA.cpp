
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

// Function to perform data regression
void RegressData(const std::vector<int>& data) {
	for (size_t i = 0; i < data.size(); i++) {
		// Perform regression analysis on each data point
		std::cout << "Regressing data point: " << data[i] << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main() {
	const size_t num_data_points = 100;
	std::vector<int> data(num_data_points);
	
	// Populate data vector with sample data
	for (size_t i = 0; i < num_data_points; i++) {
		data[i] = i;
	}

	const size_t num_threads = std::thread::hardware_concurrency();
	std::vector<std::future<void>> futures;

	// Split the data into chunks and process them in parallel
	size_t chunk_size = data.size() / num_threads + 1;
	for (size_t i = 0; i < num_threads; i++) {
		size_t start = i * chunk_size;
		size_t end = std::min((i + 1) * chunk_size, data.size());

		auto fut = std::async(std::launch::async, RegressData, std::vector<int>(data.begin() + start, data.begin() + end));
		futures.push_back(std::move(fut));
	}

	// Wait for all threads to complete
	for (auto& fut : futures) {
		fut.wait();
	}

	std::cout << "Data regression completed successfully!" << std::endl;
	return 0;
}
