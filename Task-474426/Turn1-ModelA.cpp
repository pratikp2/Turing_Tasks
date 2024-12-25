#include <iostream>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// Mutex to protect shared resources
std::mutex mtx;

// A thread-safe function that copies a string
void threadSafeStringCopy(const std::string& source, std::vector<std::unique_ptr<char[]>>& sharedStrings) {
    std::lock_guard<std::mutex> lock(mtx); // Locking to prevent data races

    // Allocate memory for the new string and copy the contents
    auto newString = std::make_unique<char[]>(source.size() + 1); // +1 for the null terminator
    std::strncpy(newString.get(), source.c_str(), source.size());
    newString[source.size()] = '\0'; // Null-terminate the string

    // Store the pointer in a thread-safe manner
    sharedStrings.push_back(std::move(newString));
}

int main() {
    std::vector<std::unique_ptr<char[]>> sharedStrings; // Vector to hold strings

    // Vector of threads
    std::vector<std::thread> threads;

    // Sample strings to copy
    std::string data[] = {"Hello, World!", "Thread-safe memory management", "C++ best practices"};

    // Create threads to perform string copying
    for (const auto& str : data) {
        threads.emplace_back(threadSafeStringCopy, str, std::ref(sharedStrings));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Output the copied strings
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock for reading the shared vector
        for (const auto& str : sharedStrings) {
            std::cout << str.get() << std::endl; // Print the copied strings
        }
    }

    return 0;
}
