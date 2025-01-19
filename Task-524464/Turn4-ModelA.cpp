#include <iostream>
#include <set>
#include <string>
#include <chrono>

// Inline comparator for std::set
inline bool compareByLength(const std::string& a, const std::string& b) {
    return a.length() < b.length();
}

int main() {
    // Create a std::set with a custom comparator (inline function)
    std::set<std::string, decltype(&compareByLength)> mySet(compareByLength);

    // Timing the insertion of elements
    auto start = std::chrono::high_resolution_clock::now();

    // Insert a large number of strings of varying lengths
    for (int i = 0; i < 100000; ++i) {
        mySet.insert("string" + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Time taken for insertions using inline comparator: " << elapsed.count() << " seconds\n";

    // Verifying size
    std::cout << "Set size: " << mySet.size() << std::endl;

    return 0;
}
