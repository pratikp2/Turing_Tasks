#include <gtest/gtest.h>
// Include the header file where your interval_pruning and calculate_result functions are declared

class IntervalPruningTest : public ::testing::Test {
 protected:
  void SetUp() override {
	// Initialize common test data or intervals here if needed
  }

  Interval pruneAndCalculate(Interval& result_int, double x, double y) {
	return interval_pruning(result_int, x, y);
  }
};

TEST_F(IntervalPruningTest, SkipsCalculationWhenWithinInterval) {
	Interval result_int(2.0, 2.0);
	double x = 1.0, y = 1.0;

	Interval updated_int = pruneAndCalculate(result_int, x, y);

	EXPECT_TRUE(updated_int.lower() == 2.0 && updated_int.upper() == 2.0);
	// Calculation should be skipped, so no need to check the result
}

TEST_F(IntervalPruningTest, PerformsCalculationWhenOutsideInterval) {
	Interval result_int(1.0, 3.0);
	double x = 2.0, y = 3.0;

	Interval updated_int = pruneAndCalculate(result_int, x, y);
	double expected_result = calculate_result(x, y);

	EXPECT_TRUE(updated_int.lower() == expected_result && updated_int.upper() == expected_result);
}

TEST_F(IntervalPruningTest, HandlesNegativeInputs) {
	Interval result_int(-5.0, 5.0);
	double x = -2.0, y = -3.0;

	Interval updated_int = pruneAndCalculate(result_int, x, y);
	double expected_result = calculate_result(x, y);

	EXPECT_TRUE(updated_int.lower() == expected_result && updated_int.upper() == expected_result);
}

TEST_F(IntervalPruningTest, HandlesZeroInputs) {
	Interval result_int(0.0, 0.0);
	double x = 0.0, y = 0.0;

	Interval updated_int = pruneAndCalculate(result_int, x, y);
	double expected_result = calculate_result(x, y);

	EXPECT_TRUE(updated_int.lower() == expected_result && updated_int.upper() == expected_result);
}

TEST_F(IntervalPruningTest, ExpandsIntervalCorrectly) {
	Interval result_int(1.0, 2.0);
	double x = 3.0, y = 4.0;

	Interval updated_int = pruneAndCalculate(result_int, x, y);

	EXPECT_TRUE(updated_int.lower() <= 11.0 && updated_int.upper() >= 11.0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
