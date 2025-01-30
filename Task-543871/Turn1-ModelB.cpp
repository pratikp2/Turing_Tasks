#include <iostream>
#include <memory>
#include <string>
#include <map>

#define HPC_OBJECT_BASE_CLASS_IMPLEMENTATION

// Base class for compute-intensive HPC objects
class HPCObject {
public:
    virtual ~HPCObject() = default;
    virtual void performComputation() = 0;
    std::string getObjectName() const { return typeid(*this).name(); }
};

// Concrete HPC object 1
class HPCObject1 : public HPCObject {
public:
    void performComputation() override {
        std::cout << "Performing computation in HPCObject1...\n";
    }
};

// Concrete HPC object 2
class HPCObject2 : public HPCObject {
public:
    void performComputation() override {
        std::cout << "Performing computation in HPCObject2...\n";
    }
};

// Enhanced Factory class using RTTI
class HPCObjectFactory {
public:
    using HPCObjectPtr = std::unique_ptr<HPCObject>;

    static HPCObjectPtr createObject(const std::string& objectType) {
        static std::map<std::string, HPCObjectPtr (*)()> creators = {
            {"HPCObject1", []() { return std::make_unique<HPCObject1>(); }},
            {"HPCObject2", []() { return std::make_unique<HPCObject2>(); }}
        };

        auto it = creators.find(objectType);
        if (it == creators.end()) {
            std::cerr << "Error: Invalid object type: " << objectType << std::endl;
            return nullptr;
        }
        return it->second();
    }
};

// Main function to demonstrate usage
int main() {
    std::string objType1 = "HPCObject1";
    std::string objType2 = "HPCObject2";
    std::string invalidObjType = "InvalidHPCObject";

    auto obj1 = HPCObjectFactory::createObject(objType1);
    auto obj2 = HPCObjectFactory::createObject(objType2);
    auto invalidObj = HPCObjectFactory::createObject(invalidObjType);

    if (obj1) {
        std::cout << "Created object: " << obj1->getObjectName() << std::endl;
        obj1->performComputation();
    }

    if (obj2) {
        std::cout << "Created object: " << obj2->getObjectName() << std::endl;
        obj2->performComputation();
    }

    if (!invalidObj) {
        std::cout << "Creation of invalid object failed." << std::endl;
    }

    return 0;
}
