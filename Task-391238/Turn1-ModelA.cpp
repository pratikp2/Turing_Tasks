#include <iostream>
#include <algorithm>

template <typename T>
class CircularBuffer {
public:
    CircularBuffer(size_t capacity) : capacity(capacity), front(0), back(0), size(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        buffer = new T[capacity];
    }

    ~CircularBuffer() {
        delete[] buffer;
    }

    void enqueue(const T& element) {
        if (size == capacity) {
            throw std::overflow_error("Buffer is full");
        }
        buffer[back] = element;
        back = (back + 1) % capacity;
        ++size;
    }

    T dequeue() {
        if (size == 0) {
            throw std::underflow_error("Buffer is empty");
        }
        T result = buffer[front];
        front = (front + 1) % capacity;
        --size;
        return result;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    size_t size() const {
        return size;
    }

    size_t capacity() const {
        return capacity;
    }

    T& frontElement() const {
        if (size == 0) {
            throw std::underflow_error("Buffer is empty");
        }
        return buffer[front];
    }

private:
    T* buffer;
    size_t capacity;
    size_t front;
    size_t back;
    size_t size;
};

int main() {
    CircularBuffer<int> buffer(5);

    for (int i = 0; i < 7; ++i) {
        buffer.enqueue(i);
        std::cout << "Enqueued: " << i << ". Buffer size: " << buffer.size() << std::endl;
    }

    while (!buffer.isEmpty()) {
        std::cout << "Dequeued: " << buffer.dequeue() << std::endl;
    }

    return 0;
}
