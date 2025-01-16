#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicDataBuffer {
private:
    double* data_ptr;
    size_t size;

public:
    DynamicDataBuffer(size_t bufferSize) {
        try {
            if (bufferSize <= 0) {
                throw runtime_error("Buffer size must be a positive integer.");
            }

            data_ptr = new double[bufferSize];
            size = bufferSize;
            cout << "Memory allocated for " << size << " elements." << endl;
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            if (data_ptr) {
                delete[] data_ptr;
                data_ptr = nullptr;
            }
            size = 0;
            throw;
        }
    }

    DynamicDataBuffer(const DynamicDataBuffer& other) {
        data_ptr = new double[other.size];
        size = other.size;

        for (size_t i = 0; i < size; ++i) {
            data_ptr[i] = other.data_ptr[i];
        }
        cout << "Memory allocated for " << size << " elements (copy)." << endl;
    }

    DynamicDataBuffer& operator=(const DynamicDataBuffer& other) {
        if (this != &other) {
            delete[] data_ptr;
            data_ptr = new double[other.size];
            size = other.size;

            for (size_t i = 0; i < size; ++i) {
                data_ptr[i] = other.data_ptr[i];
            }
            cout << "Memory reallocated for " << size << " elements (copy)." << endl;
        }
        return *this;
    }

    DynamicDataBuffer(DynamicDataBuffer&& other) noexcept {
        data_ptr = other.data_ptr;
        size = other.size;
        other.data_ptr = nullptr;
        other.size = 0;
        cout << "Memory moved for " << size << " elements." << endl;
    }

    DynamicDataBuffer& operator=(DynamicDataBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data_ptr;
            data_ptr = other.data_ptr;
            size = other.size;
            other.data_ptr = nullptr;
            other.size = 0;
            cout << "Memory moved for " << size << " elements." << endl;
        }
        return *this;
    }

    ~DynamicDataBuffer() {
        delete[] data_ptr;
        data_ptr = nullptr;
        size = 0;
        cout << "Memory deallocated." << endl;
    }

    double* getData() const {
        return data_ptr;
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    try {
        DynamicDataBuffer buffer(1000);
        // Use the buffer...

        DynamicDataBuffer bufferCopy(buffer);
        // Use bufferCopy...

        DynamicDataBuffer bufferMove(std::move(bufferCopy));
        // Use bufferMove...
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
