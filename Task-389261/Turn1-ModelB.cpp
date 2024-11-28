#include <iostream>
#include <thread>
#include <vector>
#include <boost/pool/object_pool.hpp>

// Define the object we want to allocate
class MyObject {
public:
    MyObject() : id(0) {}
    MyObject(int id) : id(id) {}
    int id;
};

// Create a thread-safe object pool using Boost.Pool
using ObjectPool = boost::pool<boost::default_user_allocator_new_delete, 
                                boost::details::pool::default_use_new_delete_allocator, 
                                boost::details::pool::default_growth_policy>::type;

// Function to allocate and deallocate objects using the object pool
void allocateAndDeallocate(ObjectPool* pool, size_t num_objects) {
    for (size_t i = 0; i < num_objects; ++i) {
        // Allocate an object from the pool
        MyObject* obj = pool->malloc();
        // Initialize the object
        new(obj) MyObject(i);

        // Use the object here
        std::cout << "Thread " << std::this_thread::get_id() << ": Allocated object " << obj->id << std::endl;

        // Deallocate the object
        pool->free(obj);
    }
}

int main() {
    const size_t num_threads = 4;
    const size_t num_objects_per_thread = 10000;

    // Create the object pool
    ObjectPool pool;

    // Start multiple threads to allocate and deallocate objects
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(allocateAndDeallocate, &pool, num_objects_per_thread));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Memory allocation/deallocation complete." << std::endl;
    return 0;
}