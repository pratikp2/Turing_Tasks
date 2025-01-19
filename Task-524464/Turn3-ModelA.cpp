#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>

// Inline function for accessing values by key
inline std::string getValue(const std::unordered_map<std::string, std::string>& map, const std::string& key) {
    auto it = map.find(key);
    return (it != map.end()) ? it->second : "Not Found";
}

// Non-inline function for accessing values by key
std::string getValueNonInline(const std::unordered_map<std::string, std::string>& map, const std::string& key) {
    auto it = map.find(key);
    return (it != map.end()) ? it->second : "Not Found";
}

int main() {
    // Create an unordered map with some values
    std::unordered_map<std::string, std::string> myMap = {
        {"apple", "A fruit"},
        {"banana", "Another fruit"},
        {"carrot", "A vegetable"}
    };

    // Timing the inline function
    auto start_inline = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        getValue(myMap, "banana");
    }
    auto end_inline = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_inline = end_inline - start_inline;
    std::cout << "Inline lookup elapsed time: " << elapsed_inline.count() << " seconds\n";

    // Timing the non-inline function
    auto start_non_inline = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        getValueNonInline(myMap, "banana");
    }
    auto end_non_inline = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_non_inline = end_non_inline - start_non_inline;
    std::cout << "Non-inline lookup elapsed time: " << elapsed_non_inline.count() << " seconds\n";

    return 0;
}
