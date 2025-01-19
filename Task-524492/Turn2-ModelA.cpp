#include <iostream>
#include <memory>
#include <vector>

class Resource {
public:
    Resource(int id) : id(id) {
        std::cout << "Resource " << id << " acquired." << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << id << " released." << std::endl;
    }

    void use() {
        std::cout << "Using resource " << id << "." << std::endl;
    }

private:
    int id;
};

void uniquePointerExample() {
    std::unique_ptr<Resource> uniqueRes(new Resource(1)); // Creating a unique pointer
    uniqueRes->use(); // Using the resource

    // No need to explicitly delete; it will automatically be released when out of scope
}

void sharedPointerExample() {
    std::shared_ptr<Resource> sharedRes1(new Resource(2)); // Creating the first shared pointer
    {
        std::shared_ptr<Resource> sharedRes2 = sharedRes1; // Copying shared pointer
        sharedRes2->use(); // Using the resource

        // sharedRes2 goes out of scope here, but the Resource remains allocated
    }
    sharedRes1->use(); // Resource is still accessible through sharedRes1
} // Resource is released here as sharedRes1 goes out of scope and no references remain.

int main() {
    uniquePointerExample();
    std::cout << "==========================" << std::endl;
    sharedPointerExample();
    return 0;
}
