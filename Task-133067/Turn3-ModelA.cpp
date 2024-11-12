Interval interval_pruning(Interval result_int, double input_x, double input_y) {
	// Calculate the minimum and maximum possible results for the calculation
	double min_result = result_int.lower() + std::min(input_x, -input_x) * std::min(input_y, -input_y);
	double max_result = result_int.upper() + std::max(input_x, -input_x) * std::max(input_y, -input_y);

	// Create a new interval based on the calculated minimum and maximum results
	Interval calculation_int(min_result, max_result);
	result_int = result_int + calculation_int;

	return result_int;
}
