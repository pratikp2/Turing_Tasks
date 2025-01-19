#include <iostream>
#include <set>
#include <string>
#include <chrono>

// Inline function for custom comparator (reverse order for strings)
inline bool reverseStringCompare(const std::string& a, const std::string& b) {
    return a > b;
}

// Non-inline function for custom comparator
bool reverseStringCompareNonInline(const std::string& a, const std::string& b) {
    return a > b;
}

int main() {
    // Create a set using the inline comparator
    std::set<std::string, decltype(reverseStringCompare)> mySetInline(reverseStringCompare);

    // Create a set using the non-inline comparator
    std::set<std::string, decltype(reverseStringCompareNonInline)> mySetNonInline(reverseStringCompareNonInline);

    // Timing for frequent insertions using inline comparator
    auto start_inline = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        mySetInline.insert(std::to_string(i) + "_" + std::to_string(i % 100));
    }
    auto end_inline = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_inline = end_inline - start_inline;
    std::cout << "Inline comparator insertion elapsed time: " << elapsed_inline.count() << " seconds\n";

    // Timing for frequent insertions using non-inline comparator
    auto start_non_inline = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        mySetNonInline.insert(std::to_string(i) + "_" + std::to_string(i % 100));
    }
    auto end_non_inline = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_non_inline = end_non_inline - start_non_inline;
    std::cout << "Non-inline comparator insertion elapsed time: " << elapsed_non_inline.count() << " seconds\n";

    return 0;
}
