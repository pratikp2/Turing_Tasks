#include <iostream>
#include <string>
#include <unordered_map>

// SingletonSubject class

// ObserverFactory class

class SecureSystem {
public:
    void initializeSystem() {
        auto observer1 = ObserverFactory::createObserver("ConcreteObserver");
        observer1->setToken("valid_token_1");

        auto observer2 = ObserverFactory::createObserver("ConcreteObserver");
        observer2->setToken("valid_token_2");

        SingletonSubject::getInstance().registerObserver(observer1->getToken(), observer1);
        SingletonSubject::getInstance().registerObserver(observer2->getToken(), observer2);

        SingletonSubject::getInstance().notifyObservers("Sensitive event data");
    }
};

int main() {
    SecureSystem system;
    system.initializeSystem();
    return 0;
}
