#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <cassert>

class BitPackedTimeSeries {
public:
    BitPackedTimeSeries(size_t size) : size_(size) {
        // Store a certain range of time series values.
        // For demonstration, supporting values from 0 to 15 (4 bits)
        capacity_ = (size_ * sizeof(uint8_t) * 8) / bits_per_value_;
        data_.resize(capacity_);
        std::fill(data_.begin(), data_.end(), 0);
    }

    void setValue(size_t index, uint8_t value) {
        assert(index < size_);
        assert(value < (1 << bits_per_value_)); // Ensure fitting value

        size_t bit_pos = index * bits_per_value_;
        size_t byte_pos = bit_pos / 8;
        size_t bit_offset = bit_pos % 8;

        // Mask to clear the bits
        uint8_t mask = (~(mask_ >> bit_offset));
        data_[byte_pos] = (data_[byte_pos] & mask) | (value << bit_offset);
    }

    uint8_t getValue(size_t index) const {
        assert(index < size_);

        size_t bit_pos = index * bits_per_value_;
        size_t byte_pos = bit_pos / 8;
        size_t bit_offset = bit_pos % 8;

        return (data_[byte_pos] >> bit_offset) & mask_;
    }

    void print() const {
        for (size_t i = 0; i < size_; ++i) {
            std::cout << static_cast<int>(getValue(i)) << " ";
        }
        std::cout << std::endl;
    }

private:
    size_t size_;                          // Total size of the time series
    size_t capacity_;                      // Actual capacity in bytes
    std::vector<uint8_t> data_;           // Bit packed data storage
    const uint8_t bits_per_value_ = 4;    // Each value is 4 bits (supports 0-15)
    const uint8_t mask_ = (1 << bits_per_value_) - 1; // All bits set for 4 bits
};

int main() {
    const size_t number_of_points = 20;

    BitPackedTimeSeries ts(number_of_points);

    // Setting some values in the time series
    for (size_t i = 0; i < number_of_points; ++i) {
        ts.setValue(i, i % 16); // Insert values in range.
    }

    // Print time series values
    ts.print();

    return 0;
}
