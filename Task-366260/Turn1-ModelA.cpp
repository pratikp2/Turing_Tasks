#include <iostream>
#include <memory>

class Resource {
public:
    Resource() {
        std::cout << "Resource constructed." << std::endl;
    }

    ~Resource() {
        std::cout << "Resource destroyed." << std::endl;
    }
};

int main() {
    // Using std::unique_ptr for single ownership
    std::unique_ptr<Resource> uniquePtr = std::make_unique<Resource>();
    
    // Transferring ownership to another unique_ptr
    std::unique_ptr<Resource> uniquePtr2 = std::move(uniquePtr);

    // Using std::shared_ptr for shared ownership
    std::shared_ptr<Resource> sharedPtr1 = std::make_shared<Resource>();
    std::shared_ptr<Resource> sharedPtr2 = sharedPtr1;

    return 0;
}