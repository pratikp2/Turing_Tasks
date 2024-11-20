#include <iostream>
#include <vector>
#include <memory>

class Example {
public:
    Example(int value) : value_(value) {}
    void print() const { std::cout << "Value: " << value_ << std::endl; }
    
    ~Example() { std::cout << "Destructor called for value: " << value_ << std::endl; }

private:
    int value_;
};

int main() {
    // Using std::unique_ptr in a vector
    std::vector<std::unique_ptr<Example>> uniquePtrVector;

    // Adding unique_ptr elements
    uniquePtrVector.push_back(std::make_unique<Example>(1));
    uniquePtrVector.push_back(std::make_unique<Example>(2));

    // Accessing elements
    for (const auto& ptr : uniquePtrVector) {
        ptr->print();
    }

    // Using std::shared_ptr in a vector
    std::vector<std::shared_ptr<Example>> sharedPtrVector;

    // Adding shared_ptr elements
    sharedPtrVector.push_back(std::make_shared<Example>(3));
    sharedPtrVector.push_back(std::make_shared<Example>(4));

    // Accessing elements
    for (const auto& ptr : sharedPtrVector) {
        ptr->print();
    }

    return 0;
}