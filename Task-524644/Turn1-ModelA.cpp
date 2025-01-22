#include <iostream>
#include <cstring>

class DynamicString {
public:
    DynamicString() : data(nullptr) {}

    // Constructor to create dynamic string from a C-style string
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
    DynamicString(DynamicString&& other) noexcept {
        data = other.data;
        other.data = nullptr; // Leave other in a safe state
    }

    // Destructor
    ~DynamicString() {
        delete[] data;
    }

    // Assignment operator
    DynamicString& operator=(const DynamicString& other) {
        if (this == &other) return *this;

        delete[] data; // Clean up existing memory

        if (other.data) {
            size_t length = strlen(other.data);
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
        return *this;
    }

    // Move assignment operator
    DynamicString& operator=(DynamicString&& other) noexcept {
        if (this == &other) return *this;

        delete[] data; // Clean up existing memory
        data = other.data;
        other.data = nullptr; // Leave other in a safe state
        return *this;
    }

    // Method to get the current string
    const char* get() const {
        return data ? data : "";
    }

    // Method to get the length of the string
    size_t length() const {
        return data ? strlen(data) : 0;
    }

private:
    char* data; // Pointer to dynamically allocated string
};

// Example usage
int main() {
    DynamicString command1("MOVE 10 20");
    DynamicString command2 = command1; // Copy
    DynamicString command3("TURN 90");

    std::cout << "Command 1: " << command1.get() << " (Length: " << command1.length() << ")" << std::endl;
    std::cout << "Command 2: " << command2.get() << " (Length: " << command2.length() << ")" << std::endl;
    std::cout << "Command 3: " << command3.get() << " (Length: " << command3.length() << ")" << std::endl;

    command3 = command1; // Assignment

    std::cout << "Command 3 after assignment: " << command3.get() << " (Length: " << command3.length() << ")" << std::endl;

    return 0;
}
