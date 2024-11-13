#include <gtest/gtest.h>
#include <boost/numeric/interval.hpp>

// ... (Rest of the code remains the same)

TEST(IntervalPruningTest, BoundaryTest) {
    Interval result_int(calculate_result(0.0, 0.0), calculate_result(0.0, 0.0));
    double input_x = 0.0;
    double input_y = 0.0;
    Interval updated_interval = interval_pruning(result_int, input_x, input_y);
    EXPECT_EQ(updated_interval.lower(), 0.0);
    EXPECT_EQ(updated_interval.upper(), 0.0);
}

TEST(IntervalPruningTest, DegenerateIntervalTest) {
    Interval result_int(calculate_result(1.0, 1.0), calculate_result(1.0, 1.0));
    double input_x = 1.0;
    double input_y = 2.0;
    Interval updated_interval = interval_pruning(result_int, input_x, input_y);
    EXPECT_EQ(updated_interval.lower(), 3.0);
    EXPECT_EQ(updated_interval.upper(), 3.0);
}

// Add more test cases as needed

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}