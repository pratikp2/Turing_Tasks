#include <iostream>
#include <cstring>

class DynamicString {
public:
    // Constructor
    DynamicString() : data(nullptr) {}

    // Constructor from C-style string
    DynamicString(const char* str) {
        if (str) {
            size_t length = strlen(str);
            data = new char[length + 1]; // +1 for the null terminator
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    // Copy constructor
    DynamicString(const DynamicString& other) {
        if (other.data) {
            size_t length = strlen(other.data);
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    // Move constructor
    DynamicString(DynamicString&& other) noexcept : data(other.data) {
        other.data = nullptr; // Leave the other object in a safe state
    }

    // Destructor
    ~DynamicString() {
        delete[] data;
    }

    // Copy assignment operator
    DynamicString& operator=(const DynamicString& other) {
        if (this != &other) {
            delete[] data; // Clean up existing memory
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

    // Move assignment operator
    DynamicString& operator=(DynamicString&& other) noexcept {
        if (this != &other) {
            delete[] data; // Clean up existing memory
            data = other.data;
            other.data = nullptr; // Leave the other object in a safe state
        }
        return *this;
    }

    // Concatenate another string
    void concatenate(const DynamicString& other) {
        if (other.data) {
            size_t newLength = (data ? strlen(data) : 0) + strlen(other.data);
            char* newData = new char[newLength + 1]; // +1 for null terminator
            
            if (data) {
                strcpy(newData, data); // Copy existing data if any
            }
            strcat(newData, other.data); // Append the new data
            
            delete[] data; // Clean up existing memory
            data = newData; // Update the pointer
        }
    }

    // Clear the string content
    void clear() {
        delete[] data; // Deallocate memory
        data = nullptr; // Reset the pointer to null
    }

    // Get the C-style string
    const char* get() const {
        return data ? data : ""; // Return an empty string if data is null
    }

    // Method to get the length of the string
    size_t length() const {
        return data ? strlen(data) : 0; // Return the length or 0 if null
    }
};

// Example usage
int main() {
    DynamicString str1("Hello");
    DynamicString str2(" World!");

    // Concatenate str2 to str1
    str1.concatenate(str2);
    std::cout << "Concatenated String: " << str1.get() << " (Length: " << str1.length() << ")" << std::endl;

    // Clear the contents of str1
    str1.clear();
    std::cout << "After Clearing: '" << str1.get() << "' (Length: " << str1.length() << ")" << std::endl;

    return 0;
}
