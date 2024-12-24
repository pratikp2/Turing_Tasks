#include <iostream>
#include <cstring>

class COWString {
private:
    struct StringData {
        char* data;
        int refCount;

        StringData(const char* str) 
            : data(new char[strlen(str) + 1]), refCount(1) {
            strcpy(data, str);
        }

        ~StringData() {
            delete[] data;
        }
    };

    StringData* stringData;

    void detach() {
        if (stringData->refCount > 1) {
            // Create a new StringData to make a copy
            StringData* newData = new StringData(stringData->data);
            newData->refCount = 1;

            // Decrease the reference count of the old data
            --stringData->refCount;

            // Update the current string data to the new one
            stringData = newData;
        }
    }

public:
    COWString(const char* str) : stringData(new StringData(str)) {}

    COWString(const COWString& other)
        : stringData(other.stringData) {
        ++stringData->refCount; // Increment refCount
    }

    COWString& operator=(const COWString& other) {
        if (this != &other) {
            // Decrease the refCount of the current data
            --stringData->refCount;

            // If the count reaches zero, delete the current data
            if (stringData->refCount == 0) {
                delete stringData;
            }
            
            // Point to the new data and increment its refCount
            stringData = other.stringData;
            ++stringData->refCount;
        }
        return *this;
    }

    ~COWString() {
        // Decrease refCount and delete if it reaches zero
        if (--stringData->refCount == 0) {
            delete stringData;
        }
    }

    const char* c_str() const {
        return stringData->data;
    }

    void set(const char* str) {
        detach(); // Ensure we have our own copy before modifying
        strcpy(stringData->data, str);
    }

    void print() const {
        std::cout << c_str() << std::endl;
    }
};

// Example usage
int main() {
    COWString str1("Hello, World!");
    COWString str2 = str1; // Copies the reference

    str1.print(); // Output: Hello, World!
    str2.print(); // Output: Hello, World!

    // Modifying str2, should invoke the copy-on-write mechanism
    str2.set("Goodbye, World!");
    str1.print(); // Output: Hello, World!
    str2.print(); // Output: Goodbye, World!

    return 0;
}
