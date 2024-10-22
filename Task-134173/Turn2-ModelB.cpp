#include <spdlog/spdlog.h>

int main() {
    try {
        std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt("app");
        logger->set_level(spdlog::level::debug);

        // ... Code that might log system errors

    } catch (const std::exception& e) {
        // Handle error securely
        std::string errorMessage = "An error occurred: ";
        errorMessage += e.what();

        // Log a generic error message for logging system errors
        spdlog::get("app")->error("Error during logging: {}", errorMessage);

        // Optionally, you can show a generic message to the user
        std::cerr << "An error has occurred. Please contact support." << std::endl;
    }
    return 0;
}