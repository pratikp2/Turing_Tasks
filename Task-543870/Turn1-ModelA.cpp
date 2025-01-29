#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <memory>
#include <exception>
#include <utility>

template<typename Func, typename... Args>
class SafeThread {
public:
    SafeThread(Func&& func, Args&&... args) 
        : _promise(std::make_shared<std::promise<void>>()),
          _thread([this, func, args...]() mutable {
              try {
                  func(std::forward<Args>(args)...);
              } catch (...) {
                  _promise->set_exception(std::current_exception());
              }
              _promise->set_value();
          }) {}

    // Deleting copy constructor and copy assignment operator
    SafeThread(const SafeThread&) = delete;
    SafeThread& operator=(const SafeThread&) = delete;

    // Move constructor and move assignment operator
    SafeThread(SafeThread&& other) noexcept
        : _thread(std::move(other._thread)),
          _promise(std::move(other._promise)) {
        other._thread = std::thread(); // Transfer ownership
    }

    SafeThread& operator=(SafeThread&& other) noexcept {
        if (this != &other) {
            if (_thread.joinable()) {
                _thread.join(); // Join the current thread before taking ownership
            }
            _thread = std::move(other._thread);
            _promise = std::move(other._promise);
        }
        return *this;
    }

    ~SafeThread() {
        if (_thread.joinable()) {
            _thread.join();
        }
    }

    void wait() {
        _promise->get_future().get();
    }

private:
    std::thread _thread;
    std::shared_ptr<std::promise<void>> _promise;
};

// Example function to run in a thread
void exampleFunction(int id, int wait_time) {
    std::cout << "Thread " << id << " started.\n";
    std::this_thread::sleep_for(std::chrono::seconds(wait_time));
    std::cout << "Thread " << id << " finished.\n";
}

int main() {
    const int num_threads = 5;
    SafeThread<void(int, int)> threads[num_threads];

    // Create and start threads
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = SafeThread<void(int, int)>(exampleFunction, i, 2);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_threads; ++i) {
        threads[i].wait();
    }

    return 0;
}
