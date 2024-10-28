#include <iostream>
#include <unordered_map>
#include <vector>

class Object {
public:
	Object() {
		GC::addObject(this);
	}

	virtual ~Object() {
		GC::removeObject(this);
	}

private:
	int refCount = 1;

friend class GC;
};

class GC {
public:
	static void addObject(Object* obj) {
		objects.push_back(obj);
	}

	static void removeObject(Object* obj) {
		for (auto it = objects.begin(); it != objects.end(); ++it) {
			if (*it == obj) {
				objects.erase(it);
				return;
			}
		}
	}

	static void collectGarbage() {
		for (Object* obj : objects) {
			if (obj->refCount == 0) {
				delete obj;
			}
		}
	}

private:
	static std::vector<Object*> objects;
};

std::vector<Object*> GC::objects;

class ScriptString : public Object {
public:
	ScriptString(const std::string& data) : data(data) {}

	std::string getData() const { return data; }

private:
	std::string data;
};

int main() {
	{
		ScriptString* str1 = new ScriptString("Hello");
		ScriptString* str2 = new ScriptString("World");

		std::cout << "Str1: " << str1->getData() << std::endl;
		std::cout << "Str2: " << str2->getData() << std::endl;

		// Manually decrement reference counts when objects go out of scope
		str1->refCount--;
		str2->refCount--;

		GC::collectGarbage();
	}

	std::cout << "Garbage collection completed." << std::endl;
	return 0;
}