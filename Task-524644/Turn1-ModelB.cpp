#include <cstring>
#include <iostream>

using namespace std;

class DynamicString {
private:
    char* data;
    size_t size;
    size_t capacity;

public:
    DynamicString() : data(nullptr), size(0), capacity(0) {}

    ~DynamicString() {
        delete[] data;
    }

    void append(const char* str) {
        size_t len = strlen(str);
        if (capacity - size < len + 1) {
            resize(capacity * 2 + len + 1);
        }
        strcpy(data + size, str);
        size += len;
    }

    void set(const char* str) {
        size_t len = strlen(str);
        resize(len + 1);
        strcpy(data, str);
        size = len;
    }

    char* c_str() const {
        return data;
    }

    size_t length() const {
        return size;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

private:
    void resize(size_t new_capacity) {
        char* new_data = new char[new_capacity];
        strcpy(new_data, data);
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

int main() {
    DynamicString command;

    cout << "Enter command string: ";
    char inputBuffer[1024]; // Assuming a maximum input length of 1023 characters (plus null terminator)
    cin.getline(inputBuffer, 1024);

    if (cin.fail()) {
        cout << "Error: Invalid input. Please enter a valid string." << endl;
        return 1;
    }

    command.set(inputBuffer);

    cout << "Command string: " << command.c_str() << endl;
    cout << "Command length: " << command.length() << endl;

    // Example of further manipulation:
    command.append(" MOV3 P1 100 200 300");

    cout << "Updated command string: " << command.c_str() << endl;

    return 0;
}
