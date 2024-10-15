// automated_gc_content_test.cpp

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <cmath>

// Function to calculate GC content (same as before)
double calculate_gc_content(const std::string& dna_sequence);

// Structure to hold test data
struct TestCase {
	std::string sequence;
	double expected_gc;
};

// Function to load test data from a file
std::vector<TestCase> load_test_cases(const std::string& test_data_file) {
	std::vector<TestCase> test_cases;
	std::ifstream file(test_data_file);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open test data file: " + test_data_file);
	}
	std::string line;
	while (std::getline(file, line)) {
		TestCase test_case;
		size_t pos = line.find('\t');
		if (pos == std::string::npos) {
			throw std::runtime_error("Invalid test data format in file: " + test_data_file);
		}
		test_case.sequence = line.substr(0, pos);
		test_case.expected_gc = std::stod(line.substr(pos + 1));
		test_cases.push_back(test_case);
	}
	file.close();
	return test_cases;
}

// Automated testing function
void run_automated_tests(const std::string& test_data_file) {
	int passed_tests = 0;
	int total_tests = 0;

	try {
		std::vector<TestCase> test_cases = load_test_cases(test_data_file);
		for (const TestCase& test_case : test_cases) {
			total_tests++;
			double result_gc = calculate_gc_content(test_case.sequence);
			if (std::abs(result_gc - test_case.expected_gc) > 0.0001) {
				std::cout << "Test Failed: Sequence: " << test_case.sequence << ", Expected GC: " << test_case.expected_gc << ", Got: " << result_gc << std::endl;
			} else {
				passed_tests++;
			}
		}
	} catch (const std::exception& e) {
		std::cout << "Error occurred during testing: " << e.what() << std::endl;
	}

	std::cout << "Test Summary: " << passed_tests << " out of " << total_tests << " tests passed." << std::endl;
}

int main() {
	// Documentation remains the same

	// Automated testing using test data file
	std::string test_data_file = "test_data.txt"; // Replace with the actual test data file
	run_automated_tests(test_data_file);

	return 0;
}