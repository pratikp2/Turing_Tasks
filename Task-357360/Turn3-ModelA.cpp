#include <iostream>
#include <list>
#include <memory>

// Base element class
class Element {
public:
    int value;
    Element(int v) : value(v) {}
};

// Derived element with intrusive link
class IntrusiveElement : public Element {
public:
    std::shared_ptr<IntrusiveElement> next;
};

// Hybrid container: non-intrusive list with intrusive link on elements
class HybridList {
private:
    std::list<std::shared_ptr<IntrusiveElement>> elements;

public:
    void push_back(const int& value) {
        elements.push_back(std::make_shared<IntrusiveElement>(value));
    }

    // Intrusive function to quickly remove an element from the list
    void removeIntrusive(const std::shared_ptr<IntrusiveElement>& element) {
        for (auto& it = elements.begin(); it != elements.end(); ++it) {
            if (it->get() == element.get()) {
                elements.erase(it);
                return;
            }
        }
    }

    void print() const {
        for (const auto& element : elements) {
            std::cout << element->value << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    HybridList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    std::cout << "Initial list:" << std::endl;
    list.print();

    // Using intrusive remove
    auto elementToRemove = std::shared_ptr<IntrusiveElement>(list.elements.front().get());
    list.removeIntrusive(elementToRemove);

    std::cout << "List after intrusive removal:" << std::endl;
    list.print();

    return 0;
}
