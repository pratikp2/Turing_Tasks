#include <iostream>
#include <cstring>

class LightweightString {
public:
    LightweightString() : data(nullptr) {}

    LightweightString(const char* str) {
        initialize(str);
    }

    LightweightString(const LightweightString& other) {
        initialize(other.data);
    }

    LightweightString(LightweightString&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    ~LightweightString() {
        delete[] data;
    }

    LightweightString& operator=(const LightweightString& other) {
        if (this != &other) {
            delete[] data;
            initialize(other.data);
        }
        return *this;
    }

    LightweightString& operator=(LightweightString&& other) noexcept {
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
        delete[] data;
        initialize(str);
    }

    void clear() {
        delete[] data;
        data = nullptr;
    }

    void concatenate(const char* str) {
        if (!data) {
            initialize(str);
        } else {
            size_t oldLength = strlen(data);
            size_t newLength = oldLength + strlen(str) + 1;
            char* temp = new char[newLength];
            strcpy(temp, data);
            strcpy(temp + oldLength, str);
            delete[] data;
            data = temp;
        }
    }

private:
    void initialize(const char* str) {
        if (str) {
            size_t length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
        }
    }

    char* data;
};

// Example usage
int main() {
    LightweightString str1("Hello");
    LightweightString str2(" World!");

    std::cout << "str1: " << str1.get() << std::endl;
    std::cout << "str2: " << str2.get() << std::endl;

    str1.concatenate(str2.get());

    std::cout << "str1 after concatenation: " << str1.get() << std::endl;

    str2.clear();

    std::cout << "str2 after clearing: " << str2.get() << std::endl;

    return 0;
}
