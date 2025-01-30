#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>

// Base class for all compute-intensive objects
class ComputeObject {
public:
    virtual void compute() = 0;
    virtual ~ComputeObject() = default;
};

// Derived classes for specific compute-intensive objects
class MatrixMultiplication : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }
};

class FourierTransform : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }
};

// Factory class to handle dynamic object creation using RTTI
class ComputeObjectFactory {
public:
    template <typename T>
    void registerType() {
        auto typeIndex = std::type_index(typeid(T));
        // Register the creator function for the type T
        creators[typeIndex] = []() -> std::unique_ptr<ComputeObject> {
            return std::make_unique<T>();
        };
    }

    std::unique_ptr<ComputeObject> create(const std::type_index& typeIndex) {
        auto it = creators.find(typeIndex);
        if (it != creators.end()) {
            return it->second(); // Call the creator function
        }
        return nullptr; // Type not registered
    }

private:
    std::unordered_map<std::type_index, std::function<std::unique_ptr<ComputeObject>()>> creators;
};

// Example usage
int main() {
    ComputeObjectFactory factory;

    // Registering the types that can be created
    factory.registerType<MatrixMultiplication>();
    factory.registerType<FourierTransform>();

    // Creating objects dynamically at runtime
    auto matrixMultObj = factory.create(std::type_index(typeid(MatrixMultiplication)));
    if (matrixMultObj) {
        matrixMultObj->compute();
    }

    auto fourierTransformObj = factory.create(std::type_index(typeid(FourierTransform)));
    if (fourierTransformObj) {
        fourierTransformObj->compute();
    }

    // Attempting to create an unregistered type
    auto unregisteredObj = factory.create(std::type_index(typeid(int))); // This will return nullptr
    if (!unregisteredObj) {
        std::cout << "Type not registered.\n";
    }

    return 0;
}
