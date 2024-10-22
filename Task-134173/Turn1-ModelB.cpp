 // Include the required header files
 #include <iostream>
 #include <stdexcept>
 #include <fmt/format.h>
 #include <spdlog/spdlog.h>
 #include <spdlog/sinks/stdout_color_sinks.h>

 // Create a custom exception class
 class SensitiveDataException : public std::runtime_error {
  public:
    SensitiveDataException(const std::string& message) : std::runtime_error(message) {}
 };

 int main() {
    // Initialize spdlog for logging
    auto console = spdlog::stdout_color_sinks_mt();
    spdlog::set_default_logger(console);

    // Function to process data
    void process_data(const std::string& input) {
        // Simulate some processing and throw an exception if sensitive data is found
        if (input.find("sensitive_data") != std::string::npos) {
            throw SensitiveDataException("Sensitive data detected in input.");
        }
    }

    std::string user_input;
    std::cout << "Enter data to process: ";
    std::getline(std::cin, user_input);

    try {
        process_data(user_input);
        std::cout << "Data processed successfully!" << std::endl;
    } catch (const SensitiveDataException& e) {
        // Log the error using spdlog with masking
        std::string masked_error = fmt::format("Error: {}", e.what());
        spdlog::error("{}", masked_error);

        // Display a generic error message to the user
        std::cout << "An error occurred while processing the data. Please try again." << std::endl;
    } catch (const std::exception& e) {
        // Handle other exceptions if needed
        spdlog::error("Unhandled exception: {}", e.what());
        std::cout << "An unexpected error occurred. Please contact support." << std::endl;
    }
    return 0;
 } 