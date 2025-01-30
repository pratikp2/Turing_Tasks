#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>

// Base class for all compute objects, with a clone() method
class ComputeObject {
public:
    virtual void compute() = 0;  // Pure virtual method
    virtual std::unique_ptr<ComputeObject> clone() const = 0; // Virtual clone method
    virtual ~ComputeObject() = default; // Virtual destructor
};

// Derived classes for specific compute-intensive objects
class MatrixMultiplication : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }

    std::unique_ptr<ComputeObject> clone() const override {
        return std::make_unique<MatrixMultiplication>(*this);
    }
};

class FourierTransform : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }

    std::unique_ptr<ComputeObject> clone() const override {
        return std::make_unique<FourierTransform>(*this);
    }
};

// Factory class to handle dynamic object creation, registration, categorization, and caching
class ComputeObjectFactory {
public:
    // Template to register types
    template <typename T>
    void registerType(const std::string& category) {
        auto typeIndex = std::type_index(typeid(T));
        creators[category][typeIndex] = []() -> std::unique_ptr<ComputeObject> {
            return std::make_unique<T>();  // Create a new instance using unique_ptr
        };
    }

    std::unique_ptr<ComputeObject> create(const std::string& category, const std::type_index& typeIndex) {
        auto categoryIt = creators.find(category);
        if (categoryIt != creators.end()) {
            auto typeIt = categoryIt->second.find(typeIndex);
            if (typeIt != categoryIt->second.end()) {
                // Check if cached object exists; creates and caches if it does not
                if (cache.find(typeIndex) == cache.end()) {
                    cache[typeIndex] = typeIt->second();  // Cache the unique_ptr object
                }
                return cache[typeIndex]->clone();  // Use clone() to return a new instance
            }
        }
        return nullptr; // Return nullptr if the type or category is not registered
    }

    // Clear the cache if needed
    void clearCache() {
        cache.clear();
    }

private:
    // Map that stores the creator functions for different categories and types
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::function<std::unique_ptr<ComputeObject>()>>> creators;

    // Cache using unique_ptr to store created instances
    std::unordered_map<std::type_index, std::unique_ptr<ComputeObject>> cache;
};

// Example usage
int main() {
    ComputeObjectFactory factory;

    // Registering types in the "linear_algebra" category
    factory.registerType<MatrixMultiplication>("linear_algebra");

    // Registering types in the "signal_processing" category
    factory.registerType<FourierTransform>("signal_processing");

    // Create objects dynamically at runtime
    auto matrixMultObj1 = factory.create("linear_algebra", std::type_index(typeid(MatrixMultiplication)));
    if (matrixMultObj1) {
        matrixMultObj1->compute();
    }

    auto matrixMultObj2 = factory.create("linear_algebra", std::type_index(typeid(MatrixMultiplication))); // This should reuse cached object
    if (matrixMultObj2) {
        matrixMultObj2->compute();
    }

    auto fourierTransformObj1 = factory.create("signal_processing", std::type_index(typeid(FourierTransform)));
    if (fourierTransformObj1) {
        fourierTransformObj1->compute();
    }

    auto fourierTransformObj2 = factory.create("signal_processing", std::type_index(typeid(FourierTransform))); // This should reuse cached object
    if (fourierTransformObj2) {
        fourierTransformObj2->compute();
    }

    // Attempting to create an unregistered type
    auto unregisteredObj = factory.create("signal_processing", std::type_index(typeid(int))); // This will return nullptr
    if (!unregisteredObj) {
        std::cout << "Type not registered within the specified category.\n";
    }

    return 0;
}
