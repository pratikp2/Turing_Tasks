#include <gtest/gtest.h>
#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<double> Interval;

// Your interval pruning function and other functions

class IntervalPruningTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Initialize any common variables or data structures here
  }

  void TearDown() override {
    // Clean up any resources allocated in SetUp here
  }
};

TEST_F(IntervalPruningTest, BoundaryTest) {
    // Test case with boundary input values
    double x1 = 0.0, y1 = 0.0, x2 = 1.0, y2 = 1.0;
    Interval result_int = calculate_result(x1, y1);
    Interval updated_interval = interval_pruning(result_int, x2, y2);
    // Assertions to check the correctness of the result
    EXPECT_TRUE(updated_interval.lower() == 2.0 && updated_interval.upper() == 2.0);
}

TEST_F(IntervalPruningTest, EdgeTest) {
    // Test case with edge input values
    double x1 = 0.0, y1 = 0.0, x2 = 0.999, y2 = 0.999;
    Interval result_int = calculate_result(x1, y1);
    Interval updated_interval = interval_pruning(result_int, x2, y2);
    // Assertions to check the correctness of the result
    EXPECT_TRUE(updated_interval.lower() >= 1.997 && updated_interval.upper() <= 2.001);
}

// Add more test cases as needed

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
