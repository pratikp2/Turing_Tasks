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

// Factory class to handle dynamic object creation with registration, categorization, and caching
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
                // Check if cached object exists
                if (cache.find(typeIndex) == cache.end()) {
                    cache[typeIndex] = typeIt->second(); // Instantiate and cache the object
                }
                return std::unique_ptr<ComputeObject>(cache[typeIndex]->clone()); // Use clone for object reuse
            }
        }
        return nullptr; // Type or category not registered
    }

    // Clear the cache if needed
    void clearCache() {
        cache.clear();
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::function<std::unique_ptr<ComputeObject>()>>> creators;

    // Cache for storing created instances
    std::unordered_map<std::type_index, std::unique_ptr<ComputeObject>> cache;
};

// Add a clone method to the base class for object reuse
class ClonableComputeObject : public ComputeObject {
public:
    virtual std::unique_ptr<ComputeObject> clone() const = 0;
};

// Modify derived classes to implement the clone method
class MatrixMultiplication : public ClonableComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }
    
    std::unique_ptr<ComputeObject> clone() const override {
        return std::make_unique<MatrixMultiplication>(*this);
    }
};

class FourierTransform : public ClonableComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }
    
    std::unique_ptr<ComputeObject> clone() const override {
        return std::make_unique<FourierTransform>(*this);
    }
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

    auto matrixMultObj2 = factory.create("linear_algebra", std::type_index(typeid(MatrixMultiplication))); // This should reuse the cached object
    if (matrixMultObj2) {
        matrixMultObj2->compute();
    }

    auto fourierTransformObj1 = factory.create("signal_processing", std::type_index(typeid(FourierTransform)));
    if (fourierTransformObj1) {
        fourierTransformObj1->compute();
    }

    auto fourierTransformObj2 = factory.create("signal_processing", std::type_index(typeid(FourierTransform))); // This should reuse the cached object
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
