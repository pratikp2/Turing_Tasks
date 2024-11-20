#include <iostream>
#include <vector>
#include <forward_list>
#include <chrono>

// Definition of the intrusive element
struct IntrusiveElement {
    int value;
    std::forward_list<IntrusiveElement>::node_type node;
};

// Function to populate containers with data
template <typename Container>
void populate_container(Container& container, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        container.emplace_front(i);
    }
}

// Function to perform iteration using a ForwardList (intrusive)
void forward_list_iteration() {
    std::forward_list<IntrusiveElement> mylist;
    const size_t data_size = 1000000;

    populate_container(mylist, data_size);
    
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    auto start = high_resolution_clock::now();

    // Using forwarding list iterator (intrusive)
    int sum = 0;
    for (auto it = mylist.begin(); it != mylist.end(); ++it) {
        sum += it->value;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);

    std::cout << "ForwardList Intrusive Iteration: " << duration.count() / 1000000 << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
}

// Function to perform iteration using a Vector (non-intrusive)
void vector_iteration() {
    std::vector<int> myvec;
    const size_t data_size = 1000000;
    
    populate_container(myvec, data_size);

    auto start = std::chrono::high_resolution_clock::now();
    
    // Using vector iterator (non-intrusive)
    int sum = 0;
    for (int& value : myvec) {
        sum += value;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Vector Non-Intrusive Iteration: " << duration.count() / 1000000 << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    std::cout << "Testing non-intrusive iterators (vector):\n";
    vector_iteration();