#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<double> Interval;

const double SIMPLE_INTERVAL_LENGTH_THRESHOLD = 1e-6;

Interval interval_pruning(Interval result_int, double input_x, double input_y) {
    // Calculate the new interval based on the input values
    Interval calculation_int(input_x * input_y);
    result_int = result_int + calculation_int;

    // Check if the interval is simple enough to use the simple pruning method
    if (std::abs(result_int.upper() - result_int.lower()) <= SIMPLE_INTERVAL_LENGTH_THRESHOLD) {
        // Use a simple interval pruning method for small intervals
        double min_x = std::min(input_x, -input_x);
        double min_y = std::min(input_y, -input_y);
        double max_x = std::max(input_x, -input_x);
        double max_y = std::max(input_y, -input_y);

        Interval x_int(min_x, max_x);
        Interval y_int(min_y, max_y);
        result_int = result_int + x_int * y_int;
    } else {
        // Use a more sophisticated interval arithmetic library or optimization technique for complex intervals
        // (You can implement this part using Boost.Interval or other libraries)
        // For now, let's use a naive approach for demonstration purposes:
        result_int = calculate_result(result_int.lower(), input_x) + calculate_result(result_int.upper(), input_y);
    }

    return result_int;
}
