// g++ -o a.out main.cpp -lboost_system

#include <iostream>
#include <boost/pool/pool.hpp>

class MyClass {
public:
	MyClass(int data) : data(data) { std::cout << "MyClass constructed: " << data << std::endl; }
	~MyClass() { std::cout << "MyClass destructed: " << data << std::endl; }
	int data;
};

int main() {
	boost::pool<> pool(sizeof(MyClass));

	{
		MyClass* obj1 = static_cast<MyClass*>(pool.malloc());
		new (obj1) MyClass(1);

		MyClass* obj2 = static_cast<MyClass*>(pool.malloc());
		new (obj2) MyClass(2);

		// Free obj1, causing fragmentation
		pool.free(obj1);

		MyClass* obj3 = static_cast<MyClass*>(pool.malloc());
		new (obj3) MyClass(3);
	}

	pool.collect(); // Perform compacting garbage collection

	return 0;
}