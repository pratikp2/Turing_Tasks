#include <iostream>
#include <cstring>
#include <type_traits>
#include <stdexcept>

template <typename T>
class UTF8String {
private:
    T* data_;
    size_t size_;

public:
    UTF8String(const T* data, size_t size) : data_(new T[size + 1]), size_(size) {
        std::copy(data, data + size, data_);
        data_[size] = '\0';
    }

    UTF8String(const UTF8String& other) : data_(new T[other.size_ + 1]), size_(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
        data_[size_] = '\0';
    }

    ~UTF8String() {
        delete[] data_;
    }

    UTF8String& operator=(const UTF8String& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.size_ + 1];
            std::copy(other.data_, other.data_ + other.size_, data_);
            size_ = other.size_;
            data_[size_] = '\0';
        }
        return *this;
    }

    size_t size() const {
        return size_;
    }

    const T* data() const {
        return data_;
    }

    template <typename U>
    friend void printUTF8(const U* str);
};

template <typename T>
void printUTF8(const T* str) {
    const UTF8String<T> utf8Str(str, std::strlen(str));
    for (size_t i = 0; i < utf8Str.size(); ++i) {
        std::cout << utf8Str.data()[i];
    }
    std::cout << std::endl;
}

int main() {
    char utf8Data1[] = "Hello, \xc3\xa9 monde!"; // UTF-8 encoded string with é (U+00E9)

    printUTF8(utf8Data1);

    return 0;
}
