#include <iostream>
#include <cstring>
#include <cassert>

class DynamicString {
public:
    DynamicString() : data(nullptr) {}

    DynamicString(const char* str) {
        if (str) {
            size_t length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    DynamicString(const DynamicString& other) {
        if (other.data) {
            size_t length = strlen(other.data);
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    DynamicString(DynamicString&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    ~DynamicString() {
        delete[] data;
    }

    DynamicString& operator=(const DynamicString& other) {
        if (this != &other) {
            delete[] data;
            if (other.data) {
                size_t length = strlen(other.data);
                data = new char[length + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    DynamicString& operator=(DynamicString&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    const char* get() const {
        return data ? data : "";
    }

    void set(const char* str) {
        delete[] data; // Clean up old data
        if (str) {
            size_t length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

private:
    char* data; 
};

class DynamicStringArray {
public:
    DynamicStringArray(size_t initialSize) 
        : size(initialSize), count(0), strings(new DynamicString[initialSize]) {
    }

    ~DynamicStringArray() {
        delete[] strings;
    }

    void add(const char* str) {
        if (count < size) { // Check if there's space to add
            strings[count++].set(str);
        } else {
            std::cerr << "Array is full. Cannot add more strings.\n";
        }
    }

    void update(size_t index, const char* str) {
        assert(index < count); // Ensure index is within bounds
        strings[index].set(str);
    }

    const char* get(size_t index) const {
        assert(index < count); // Ensure index is within bounds
        return strings[index].get();
    }

    size_t getCount() const {
        return count;
    }

private:
    size_t size;          // Total size of the array
    size_t count;         // Current number of strings in use
    DynamicString* strings; // Dynamic array of strings
};

// Example usage
int main() {
    DynamicStringArray stringArray(5);

    stringArray.add("Configuration 1");
    stringArray.add("Configuration 2");
    stringArray.add("Configuration 3");

    std::cout << "Initial Configurations:\n";
    for (size_t i = 0; i < stringArray.getCount(); ++i) {
        std::cout << stringArray.get(i) << std::endl;
    }

    // Update a configuration
    stringArray.update(1, "Updated Configuration 2");

    std::cout << "\nConfigurations after updating index 1:\n";
    for (size_t i = 0; i < stringArray.getCount(); ++i) {
        std::cout << stringArray.get(i) << std::endl;
    }

    return 0;
}
