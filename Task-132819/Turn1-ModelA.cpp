#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to perform data segmentation
std::vector<std::vector<int>> optimizedSegmentation(const std::vector<int>& data, int threshold) {
	std::vector<std::vector<int>> segments;
	std::vector<int> current_segment;

	for (int value : data) {
		if (current_segment.empty() || std::abs(current_segment.back() - value) <= threshold) {
			current_segment.push_back(value);
		} else {
			segments.push_back(current_segment);
			current_segment = {value};
		}
	}

	if (!current_segment.empty()) {
		segments.push_back(current_segment);
	}

	return segments;
}

int main() {
	std::vector<int> data = {1, 5, 8, 4, 12, 15, 18, 22, 25, 27, 30, 2, 4, 7, 10};
	int threshold = 3;

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::vector<int>> segments = optimizedSegmentation(data, threshold);

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Data Segments: " << std::endl;
	for (const auto& segment : segments) {
		for (const int& value : segment) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;
	return 0;
}