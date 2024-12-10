#include <iterator>
#include <stdexcept>

// Lazy list element
class LazyListElement {
public:
    int value;
    std::shared_ptr<LazyListElement> next;

    LazyListElement(int value, std::shared_ptr<LazyListElement> next = nullptr)
        : value(value), next(next) {}
};

// Lazy bidirectional iterator
template <typename T>
class LazyBidirectionalIterator : public std::bidirectional_iterator_tag {
public:
    using value_type = T;
    using pointer = std::shared_ptr<LazyListElement>;

    LazyBidirectionalIterator() : current(nullptr) {}

    LazyBidirectionalIterator(pointer current) : current(current) {}

    LazyBidirectionalIterator& operator++() {
        if (!current) {
            throw std::out_of_range("Iterator is at the end");
        }
        current = current->next;
        return *this;
    }

    LazyBidirectionalIterator operator++(int) {
        LazyBidirectionalIterator ret = *this;
        ++*this;
        return ret;
    }

    LazyBidirectionalIterator& operator--() {
        if (!current) {
            throw std::out_of_range("Iterator is at the beginning");
        }
        // To move backward, we need to maintain a previous pointer.
        // This example assumes a simple list where each element points to the next.
        // In a more complex implementation, you'd need to store the previous element.
        std::shared_ptr<LazyListElement> prev;
        while (current->next) {
            prev = current;
            current = current->next;
        }
        current = prev;
        return *this;
    }

    LazyBidirectionalIterator operator--(int) {
        LazyBidirectionalIterator ret = *this;
        --*this;
        return ret;
    }

    bool operator==(const LazyBidirectionalIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const LazyBidirectionalIterator& other) const {
        return !(*this == other);
    }

    T& operator*() {
        if (!current) {
            throw std::out_of_range("Iterator is out of bounds");
        }
        return current->value;
    }

    pointer operator->() {
        return current;
    }

private:
    pointer current;
};

// Lazy list class
template <typename T>
class LazyList {
public:
    using iterator = LazyBidirectionalIterator<T>;
    using const_iterator = LazyBidirectionalIterator<const T>;

    LazyList() : head(nullptr) {}

    // Lazy generation of list elements
    void generate(int size) {
        head = std::make_shared<LazyListElement>(0);
        std::shared_ptr<LazyListElement> current = head;
        for (int i = 1; i < size; ++i) {
            current->next = std::make_shared<LazyListElement>(i);
            current = current->next;
        }
    }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(); }

    const_iterator begin() const { return const_iterator(head); }
    const_iterator end() const { return const_iterator(); }

private:
    pointer head;
};

// Example usage of the Lazy List
int main() {
    const int listSize = 1000000;
    LazyList<int> lazyList;
    lazyList.generate(listSize);

    // Using algorithms with bidirectional iterators
    int sum = std::accumulate(lazyList.begin(), lazyList.end(), 0);

    std::cout << "Sum of the first " << listSize << " numbers: " << sum << std::endl;

    return 0;
}
