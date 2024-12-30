#include <iostream>
#include <vector>
#include <array>

const int NUM_BITS_PER_WORD = 32; // Assuming 32-bit integer
const int NUM_DAYS_IN_WEEK = 7;

class BitwiseTimeSeries {
private:
    std::vector<uint32_t> data;

public:
    BitwiseTimeSeries(int num_weeks) {
        int num_words = (num_weeks * NUM_DAYS_IN_WEEK) / NUM_BITS_PER_WORD + (1 if ((num_weeks * NUM_DAYS_IN_WEEK) % NUM_BITS_PER_WORD > 0) else 0);
        data.resize(num_words);
    }

    // Set the state (true or false) for a specific day and week
    void set_state(int week, int day, bool state) {
        int word_index = (week * NUM_DAYS_IN_WEEK + day) / NUM_BITS_PER_WORD;
        int bit_index = (week * NUM_DAYS_IN_WEEK + day) % NUM_BITS_PER_WORD;
        uint32_t mask = 1U << bit_index;
        if (state) {
            data[word_index] |= mask;
        } else {
            data[word_index] &= ~mask;
        }
    }

    // Get the state for a specific day and week
    bool get_state(int week, int day) {
        int word_index = (week * NUM_DAYS_IN_WEEK + day) / NUM_BITS_PER_WORD;
        int bit_index = (week * NUM_DAYS_IN_WEEK + day) % NUM_BITS_PER_WORD;
        uint32_t mask = 1U << bit_index;
        return (data[word_index] & mask) != 0;
    }

    // Count the number of set bits (true values) in a specific week
    int count_set_bits_in_week(int week) {
        int start_index = week * NUM_DAYS_IN_WEEK / NUM_BITS_PER_WORD;
        int end_index = start_index + (NUM_DAYS_IN_WEEK + NUM_BITS_PER_WORD - 1) / NUM_BITS_PER_WORD;
        int count = 0;
        for (int i = start_index; i < end_index; ++i) {
            count += __builtin_popcount(data[i]);
        }
        return count;
    }
};

int main() {
    const int num_weeks = 52;
    BitwiseTimeSeries time_series(num_weeks);

    // Set some sample states
    time_series.set_state(0, 2, true); // Monday of week 0 is true
    time_series.set_state(1, 5, true); // Friday of week 1 is true
    time_series.set_state(26, 3, true); // Wednesday of week 26 is true

    // Check some states
    std::cout << "Monday of week 0: " << (time_series.get_state(0, 0) ? "true" : "false") << std::endl;
    std::cout << "Friday of week 1: " << (time_series.get_state(1, 4) ? "true" : "false") << std::endl;
    std::cout << "Count of set bits in week 26: " << time_series.count_set_bits_in_week(26) << std::endl;

    return 0;
}
