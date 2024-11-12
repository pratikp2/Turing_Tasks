#include <iostream>
#include <boost/numeric/interval.hpp>

namespace interval = boost::numeric::interval_lib;

typedef interval::interval<double> Interval;

double calculate_result(double x, double y) {
    // Replace this with your actual exercise calculation function
    return x + y;
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
    return result_int;
}

int main() {
    double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;

    // Initialization of interval 
    Interval result_int(calculate_result(x1, y1), calculate_result(x1, y1));
    
    if (!(result_int.is_singleton())) {
        // Perform the first calculation
        double result = calculate_result(x1, y1);
        std::cout << "Result: " << result << std::endl;
        result_int = Interval(result, result);
    }

    // Perform interval pruning for the second calculation
    Interval updated_interval = interval_pruning(result_int, x2, y2);

    if (updated_interval.contains(calculate_result(x2, y2))) {
        // If the calculation result is within the updated interval, skip the calculation
        std::cout << "Calculation can be skipped." << std::endl;
    } else {
        // Perform the second calculation as the interval has been expanded.
        double result = calculate_result(x2, y2);
        std::cout << "Result: " << result << std::endl;
        result_int = Interval(result, result);
    }
    return 0;
}