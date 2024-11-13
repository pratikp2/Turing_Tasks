#include <gtest/gtest.h>
// Include the header file where your interval_pruning and calculate_result functions are declared

class IntervalPruningTest : public ::testing::Test {
 protected:
  void SetUp() override {
	// Initialize common test data or intervals here if needed
  }

  Interval pruneAndCalculate(Interval& result_int, double x, double y) {
	result_int = interval_pruning(result_int, x, y);
	double result = calculate_result(x, y);
	return Interval(result, result);
  }
};

TEST_F(IntervalPruningTest, BasicPruningTest) {
	Interval result_int(2.0, 2.0);
	double x = 1.0, y = 3.0;
	Interval expected_interval(5.0, 5.0);

	Interval updated_interval = pruneAndCalculate(result_int, x, y);
	EXPECT_EQ(updated_interval, expected_interval);
}

TEST_F(IntervalPruningTest, SkipsCalculationTest) {
	Interval result_int(5.0, 5.0);
	double x = 2.0, y = 3.0;

	Interval updated_interval = pruneAndCalculate(result_int, x, y);
	// Since the calculation result is within the updated interval, it should skip
}

TEST_F(IntervalPruningTest, HandlesNegativeInputsTest) {
	Interval result_int(-2.0, 2.0);
	double x = -1.0, y = -3.0;
	Interval expected_interval(-6.0, -6.0);

	Interval updated_interval = pruneAndCalculate(result_int, x, y);
	EXPECT_EQ(updated_interval, expected_interval);
}

TEST_F(IntervalPruningTest, ExpandsIntervalTest) {
	Interval result_int(1.0, 3.0);
	double x = 4.0, y = 2.0;
	Interval expected_interval(10.0, 14.0);

	Interval updated_interval = pruneAndCalculate(result_int, x, y);
	EXPECT_EQ(updated_interval, expected_interval);
}

// Add more test cases as needed

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}