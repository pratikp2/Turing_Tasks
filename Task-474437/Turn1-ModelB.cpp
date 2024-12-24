#include <iostream>
#include <mutex>

class COWString {
public:
    COWString() : data(nullptr), count(1), mutex() {}

    COWString(const char* str) : data(new char[strlen(str) + 1]), count(1), mutex() {
        strcpy(data, str);
    }

    COWString(const COWString& other) : data(other.data), count(other.count), mutex(other.mutex) {
        ++(*count);
    }

    ~COWString() {
        std::lock_guard<std::mutex> lock(mutex);
        if (--(*count) == 0) {
            delete[] data;
            data = nullptr;
        }
    }

    COWString& operator=(const COWString& other) {
        if (this != &other) {
            std::lock_guard<std::mutex> lock(other.mutex);
            if (--(*count) == 0) {
                delete[] data;
            }
            data = other.data;
            count = other.count;
            ++(*count);
        }
        return *this;
    }

    char* c_str() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (*count > 1) {
            data = new char[strlen(data) + 1];
            strcpy(data, data);
            *count = 1;
        }
        return data;
    }

    size_t length() const {
        return strlen(c_str());
    }

private:
    char* data;
    int* count;
    mutable std::mutex mutex;
};

void printString(const COWString& str) {
    std::cout << str.c_str() << std::endl;
}

int main() {
    COWString str1("Hello, World!");
    printString(str1);  // Output: Hello, World!

    COWString str2 = str1;
    printString(str2);  // Output: Hello, World!

    str2 = "Modified String";
    printString(str1);  // Output: Hello, World!
    printString(str2);  // Output: Modified String

    return 0;
}
