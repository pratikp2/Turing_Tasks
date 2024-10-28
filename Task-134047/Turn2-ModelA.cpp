#include <iostream>
#include <vector>
#include <memory>

// Simple class to represent an object with a varying lifetime
class MyClass {
public:
	MyClass(int data) : data(data) { std::cout << "MyClass constructed: " << data << std::endl; }
	~MyClass() { std::cout << "MyClass destructed: " << data << std::endl; }
	int data;
};

int main() {
	{
		std::vector<std::shared_ptr<MyClass>> shortLivedObjects;
		for (int i = 0; i < 10; ++i) {
			shortLivedObjects.push_back(std::make_shared<MyClass>(i));
		}
	} // shortLivedObjects goes out of scope, and its memory is automatically freed

	std::shared_ptr<MyClass> longLivedObject = std::make_shared<MyClass>(100);

	// Simulate some work with longLivedObject
	for (int i = 0; i < 100000; ++i) {
		// Do something with longLivedObject
	}

	return 0;
}