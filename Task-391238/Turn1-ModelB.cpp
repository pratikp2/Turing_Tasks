#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    size_t head;
    size_t tail;
    size_t capacity;

public:
    explicit CircularBuffer(size_t size) : buffer(size), head(0), tail(0), capacity(size) {
        if (capacity == 0) {
            throw std::invalid_argument("Buffer capacity must be greater than zero.");
        }
    }

    bool is_empty() const {
        return head == tail;
    }

    bool is_full() const {
        return (tail + 1) % capacity == head;
    }

    size_t size() const {
        return (capacity - head + tail) % capacity;
    }

    void push(const T& item) {
        if (is_full()) {
            throw std::runtime_error("Buffer is full.");
        }
        buffer[tail] = item;
        tail = (tail + 1) % capacity;
    }

    T pop() {
        if (is_empty()) {
            throw std::runtime_error("Buffer is empty.");
        }
        T item = buffer[head];
        head = (head + 1) % capacity;
        return item;
    }

    T& front() {
        if (is_empty()) {
            throw std::runtime_error("Buffer is empty.");
        }
        return buffer[head];
    }

    const T& front() const {
        if (is_empty()) {
            throw std::runtime_error("Buffer is empty.");
        }
        return buffer[head];
    }

    T& back() {
        if (is_empty()) {
            throw std::runtime_error("Buffer is empty.");
        }
        return buffer[(tail - 1 + capacity) % capacity];
    }

    const T& back() const {
        if (is_empty()) {
            throw std::runtime_error("Buffer is empty.");
        }
        return buffer[(tail - 1 + capacity) % capacity];
    }
};
 
 int main() {
    try {
        CircularBuffer<int> buffer(5);

        // Push some data into the buffer
        buffer.push(1);
        buffer.push(2);
        buffer.push(3);

        // Display the front and back elements
        std::cout << "Front: " << buffer.front() << std::endl;
        std::cout << "Back: " << buffer.back() << std::endl;

        // Pop and display elements
        while (!buffer.is_empty()) {
            std::cout << "Popping: " << buffer.pop() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
