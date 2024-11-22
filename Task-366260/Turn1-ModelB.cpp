#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Example {
public:
    Example() {
        cout << "Example object constructed." << endl;
    }
    
    ~Example() {
        cout << "Example object destroyed." << endl;
    }
};

int main() {
    // Using std::unique_ptr for single ownership
    unique_ptr<Example> example1(new Example());  // Correct way to use new
    // example1 = new Example();  // Wrong way to use new, will cause memory leak

    // Using std::shared_ptr for shared ownership
    shared_ptr<Example> example2(new Example());
    shared_ptr<Example> example3 = example2;  // Sharing ownership

    // Using std::make_unique for creating unique pointers (C++14 or later)
    unique_ptr<Example> example4 = make_unique<Example>();  // Preferred way to use new

    // Using std::vector for arrays (recommended)
    vector<unique_ptr<Example>> examples;
    examples.push_back(make_unique<Example>());
    examples.push_back(make_unique<Example>());

    // No need to use 'delete' explicitly, smart pointers will handle it

    return 0;
}