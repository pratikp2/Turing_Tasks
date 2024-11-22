#include <iostream>
#include <deque>  // Use deque for dynamic filtering due to efficient push_front/pop_back operations
#include <algorithm>
#include <functional>

// Example of a simple dynamic filter: Moving Average Filter
template <typename T>
class MovingAverageFilter {
public:
    MovingAverageFilter(size_t windowSize) : windowSize(windowSize) {}

    T filter(T newSample) {
        samples.push_front(newSample);
        if (samples.size() > windowSize) {
            samples.pop_back();
        }

        // Calculate the sum using STL accumulate algorithm
        T sum = std::accumulate(samples.begin(), samples.end(), T(0));

        // Return the average by dividing the sum by the window size
        return sum / static_cast<T>(samples.size());
    }

private:
    size_t windowSize;
    std::deque<T> samples;
};

int main() {
    // Example usage:
    std::deque<float> rawData{2.3, 4.5, 5.6, 3.4, 2.1, 4.3, 5.7};
    MovingAverageFilter<float> filter(3);  // Filter window size of 3

    // Use STL for_each algorithm to apply the filter and print the filtered values
    std::for_each(rawData.begin(), rawData.end(), [&filter](float sample) {
        float filteredValue = filter.filter(sample);
        std::cout << "Filtered Value: " << filteredValue << std::endl;
    });

    return 0;
}
