#include <iostream>
#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<double> Interval;

const double expansion_factor = 1.01; // Initial expansion factor

Interval interval_pruning(Interval result_int, double input_x, double input_y) {
	// Calculate the minimum and maximum possible results of the calculation
	double min_result = input_x * input_y;
	double max_result = input_x * input_y;

	// Expand the result interval based on the calculated minimum and maximum results
	double expansion_width = std::abs(max_result - min_result) * expansion_factor;
	result_int = Interval(min_result - expansion_width, max_result + expansion_width);

	return result_int;
}

int main() {
	double x1, y1, x2, y2;
	std::cin >> x1 >> y1 >> x2 >> y2;

	Interval result_int(calculate_result(x1, y1), calculate_result(x1,y1));
	result_int = interval_pruning(result_int, x2, y2);

	return 0;
}