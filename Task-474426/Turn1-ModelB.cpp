#include <iostream>
#include <atomic>
#include <stdexcept>
#include <memory>
#include <thread>
#include <mutex>
#include <cstring>

using namespace std;

// Thread-safe shared C-string using a unique pointer with mutex control
class ThreadSafeCString {
public:
    ThreadSafeCString(const char *str = nullptr) {
        if (str) {
            data = make_unique<char[]>(strlen(str) + 1);
            strcpy(data.get(), str);
        } else {
            data = make_unique<char[]>(1);
            data[0] = '\0';
        }
    }

    ~ThreadSafeCString() = default;

    ThreadSafeCString(ThreadSafeCString &&other) {
        data.swap(other.data);
    }

    ThreadSafeCString &operator=(ThreadSafeCString &&other) {
        data.swap(other.data);
        return *this;
    }

    // Repeatedly assign and copy a string concurrently
    void stressTest() const {
        const int numRuns = 10000;

        for (int i = 0; i < numRuns; ++i) {
            ThreadSafeCString copy(*this); // or thread-safe assignment using Lock
        }
    }

    // Atomic substitution (a thread-safe assignment)
    void setString(const char *str) {
        lock_guard<mutex> lock(m);
        if (str) {
            auto new_data = make_unique<char[]>(strlen(str) + 1);
            strcpy(new_data.get(), str);
            data.swap(new_data);
        } else {
            data = make_unique<char[]>(1);
            data[0] = '\0';
        }
    }

    // Atomic reading (thread-safe access)
    const char *getString() const {
        lock_guard<mutex> lock(m);
        return data.get();
    }

private:
    mutable mutex m;
    unique_ptr<char[]> data;
};

void threadedAccess(ThreadSafeCString &cstring) {
    try {
        // Async access for several calls, helps in highlighting memory leak
        cstring.stressTest();
        cstring.setString("Threaded modification");
        cout << "Current C-string in thread: " << cstring.getString() << endl;
    } catch (const std::exception &e) {
        cout << "Error in threaded access: " << e.what() << endl;
    }
}

int main() {
    ThreadSafeCString sharedString("Initial C-string");
    cout << "Initial C-string: " << sharedString.getString() << endl;

    thread t1(threadedAccess, ref(sharedString));
    thread t2(threadedAccess, ref(sharedString));

    // Wait for threads to finish
    t1.join();
    t2.join();

    cout << "Final C-string in main thread: " << sharedString.getString() << endl;

    return 0;
}
