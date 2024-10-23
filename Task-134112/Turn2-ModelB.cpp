#include <iostream>
#include <boost/exception/all.hpp>

// Define a custom exception class
class InvalidInputException : public boost::exception, public boost::error_info<struct tag_error_message, std::string> {
public:
    InvalidInputException(const std::string& message) : boost::exception(), boost::error_info<struct tag_error_message, std::string>(message) {}
};

// Function that performs some operation and may throw an exception
int divide(int numerator, int denominator) {
    if (denominator == 0) {
        BOOST_THROW_EXCEPTION(InvalidInputException("Cannot divide by zero"));
    }
    return numerator / denominator;
}

int main() {
    try {
        int result = divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const InvalidInputException& e) {
        // Handle the exception
        std::cerr << "Error: " << boost::diagnostic_information(e) << std::endl;
    } catch (const boost::exception& e) {
        // Handle other boost exceptions
        std::cerr << "Error: " << boost::diagnostic_information(e) << std::endl;
    } catch (const std::exception& e) {
        // Handle standard exceptions
        std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
        // Handle unknown exceptions
        std::cerr << "Error: Unknown exception occurred." << std::endl;
    }

    return 0;
}