#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

enum class ErrorCode {
    SUCCESS,
    INVALID_INPUT,
    FILE_NOT_FOUND,
    NETWORK_ERROR
};

std::atomic<bool> error_occured = false;
std::mutex mtx;
std::condition_variable cv;
std::string error_message;

void processWork(const ErrorCode& error) {
    std::thread work_thread([&]() {
        switch (error) {
            case ErrorCode::SUCCESS:
                std::cout << "Work completed successfully on thread "
                           << std::this_thread::get_id() << std::endl;
                break;
            case ErrorCode::INVALID_INPUT:
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    error_message = "Invalid input data encountered.";
                    error_occured = true;
                    cv.notify_all();
                }
                break;
            case ErrorCode::FILE_NOT_FOUND:
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    error_message = "File not found.";
                    error_occured = true;
                    cv.notify_all();
                }
                break;
            case ErrorCode::NETWORK_ERROR:
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    error_message = "Network error occurred.";
                    error_occured = true;
                    cv.notify_all();
                }
                break;
        }
    });
    work_thread.join();
}

int main() {
    ErrorCode errors[] = {
        ErrorCode::INVALID_INPUT,
        ErrorCode::FILE_NOT_FOUND,
        ErrorCode::SUCCESS,
        ErrorCode::NETWORK_ERROR
    };

    for (ErrorCode error : errors) {
        processWork(error);
        
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{ return error_occured; });
            if (error_occured) {
                std::cout << "Error on thread " << std::this_thread::get_id() 
                          << ": " << error_message << std::endl;
                error_occured = false;
            }
        }
    }

    return 0;
}
