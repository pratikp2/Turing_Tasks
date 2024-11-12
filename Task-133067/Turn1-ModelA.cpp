#include <iostream>
#include <vector>
#include <boost/icl/interval_set.hpp>

namespace icl = boost::icl;

// Function to perform repetitive calculations
double calculateExerciseValue(double x) {
	// Replace this with your actual repetitive calculation
	return x * x;
}

// Struct to represent an interval and its corresponding result
struct IntervalResult {
	icl::interval<double> interval;
	double result;
};

// Perform interval pruning and calculate results for non-overlapping intervals
std::vector<IntervalResult> optimizeCalculations(const std::vector<icl::interval<double>>& intervals) {
	std::vector<IntervalResult> results;

	// Sort the intervals based on their lower bound
	std::sort(intervals.begin(), intervals.end(), [](const icl::interval<double>& a, const icl::interval<double>& b) {
		return a.lower() < b.lower();
	});

	for (const icl::interval<double>& interval : intervals) {
		bool isOverlapping = false;

		// Check for overlap with existing results
		for (const IntervalResult& res : results) {
			if (res.interval.overlaps(interval)) {
				isOverlapping = true;
				break;
			}
		}

		if (!isOverlapping) {
			double result = calculateExerciseValue(interval.lower());
			results.push_back({interval, result});
		}
	}

	return results;
}

int main() {
	std::vector<icl::interval<double>> intervals = {
		{1.0, 5.0}, {3.0, 7.0}, {8.0, 10.0}, {2.0, 4.0}, {6.0, 9.0}
	};

	std::vector<IntervalResult> optimizedResults = optimizeCalculations(intervals);

	// Display the optimized results
	for (const IntervalResult& res : optimizedResults) {
		std::cout << "Interval: [" << res.interval.lower() << ", " << res.interval.upper() << "], Result: " << res.result << std::endl;
	}
	return 0;
}
