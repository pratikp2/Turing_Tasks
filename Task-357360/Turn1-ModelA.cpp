#include <iostream>
#include <list>
#include <vector>

// Non-intrusive iterator example using std::list
void nonIntrusiveIterators() {
    std::list<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);

    std::cout << "Non-intrusive iterators example:" << std::endl;
    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Removing an element
    myList.erase(myList.begin());
    std::cout << "After removing the first element:" << std::endl;
    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Intrusive iterator example using a custom element class
class IntrusiveElement {
public:
    int value;
    IntrusiveElement* next;

    IntrusiveElement(int v) : value(v), next(nullptr) {}
};

void intrusiveIterators() {
    std::list<IntrusiveElement*> myList;
    myList.push_back(new IntrusiveElement(1));
    myList.push_back(new IntrusiveElement(2));
    myList.push_back(new IntrusiveElement(3));

    std::cout << "Intrusive iterators example:" << std::endl;
    for (std::list<IntrusiveElement*>::iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << (*it)->value << " ";
    }
    std::cout << std::endl;

    // Removing an element
    myList.erase(myList.begin());
    std::cout << "After removing the first element:" << std::endl;
    for (std::list<IntrusiveElement*>::iterator it = myList.begin(); it != myList.end(); ++it) {
        std::cout << (*it)->value << " ";
    }
    std::cout << std::endl;

    // Clean up memory
    for (std::list<IntrusiveElement*>::iterator it = myList.begin(); it != myList.end(); ++it) {
        delete *it;
    }
    myList.clear();
}

int main() {
    nonIntrusiveIterators();
    intrusiveIterators();
    return 0;
}
