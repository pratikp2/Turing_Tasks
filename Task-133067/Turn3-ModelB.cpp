#include <iostream>
#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<double> Interval;

const double EPSILON = 0.0001; // Small value for precision control

double calculate_result(double x, double y) {
    return x + y; // Example implementation, replace with actual function logic
}

Interval interval_pruning(Interval result_int, double input_x, double input_y) {
    // Expand the result interval based on the bounds of the calculation
    double min_x = std::min(input_x, -input_x);
    double min_y = std::min(input_y, -input_y);
    double max_x = std::max(input_x, -input_x);
    double max_y = std::max(input_y, -input_y);

    Interval x_int(min_x, max_x);
    Interval y_int(min_y, max_y);
    Interval calculation_int(x_int * y_int);
    result_int = result_int + calculation_int;

    // Dynamically adjust the interval bounds based on the precision of the calculation
    double precision = std::abs(result_int.upper() - result_int.lower()) / 2;
    result_int = Interval(result_int.lower() - precision, result_int.upper() + precision);

    return result_int;
}

int main() {
    double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    Interval result_int = calculate_result(x1, y1);
    result_int = Interval(result_int.lower() - EPSILON, result_int.upper() + EPSILON);

    Interval updated_interval = interval_pruning(result_int, x2, y2);

    // Check if the calculation result is within the updated interval
    double result_check = calculate_result(x2, y2);
    if (result_check >= updated_interval.lower() && result_check <= updated_interval.upper()) {
        std::cout << "Calculation can be skipped." << std::endl;
    } else {
        std::cout << "Result: " << result_check << std::endl;
    }
    return 0;
} 