#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>

// Base class for all compute objects
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

// Factory class to handle dynamic object creation with registration and categorization
class ComputeObjectFactory {
public:
    template <typename T>
    void registerType(const std::string& category) {
        auto typeIndex = std::type_index(typeid(T));
        creators[category][typeIndex] = []() -> std::unique_ptr<ComputeObject> {
            return std::make_unique<T>();
        };
    }

    std::unique_ptr<ComputeObject> create(const std::string& category, const std::type_index& typeIndex) {
        auto categoryIt = creators.find(category);
        if (categoryIt != creators.end()) {
            auto typeIt = categoryIt->second.find(typeIndex);
            if (typeIt != categoryIt->second.end()) {
                return typeIt->second(); // Instantiate the object
            }
        }
        return nullptr; // Type or category not registered
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::function<std::unique_ptr<ComputeObject>()>>> creators;
};

// Example usage
int main() {
    ComputeObjectFactory factory;

    // Registering types in the "linear_algebra" category
    factory.registerType<MatrixMultiplication>("linear_algebra");
    
    // Registering types in the "signal_processing" category
    factory.registerType<FourierTransform>("signal_processing");

    // Create objects dynamically at runtime
    auto matrixMultObj = factory.create("linear_algebra", std::type_index(typeid(MatrixMultiplication)));
    if (matrixMultObj) {
        matrixMultObj->compute();
    }

    auto fourierTransformObj = factory.create("signal_processing", std::type_index(typeid(FourierTransform)));
    if (fourierTransformObj) {
        fourierTransformObj->compute();
    }

    // Attempting to create an unregistered type
    auto unregisteredObj = factory.create("signal_processing", std::type_index(typeid(int))); // This will return nullptr
    if (!unregisteredObj) {
        std::cout << "Type not registered within the specified category.\n";
    }

    return 0;
}
