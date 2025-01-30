#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>

// Base class for all compute objects, now including a clone() method
class ComputeObject {
public:
    virtual void compute() = 0;
    virtual std::shared_ptr<ComputeObject> clone() const = 0; // Add clone() method
    virtual ~ComputeObject() = default;
};

// Derived classes for specific compute-intensive objects
class MatrixMultiplication : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }

    std::shared_ptr<ComputeObject> clone() const override {
        return std::make_shared<MatrixMultiplication>(*this);
    }
};

class FourierTransform : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }

    std::shared_ptr<ComputeObject> clone() const override {
        return std::make_shared<FourierTransform>(*this);
    }
};

// Factory class to handle dynamic object creation with registration, categorization, and caching using shared_ptr
class ComputeObjectFactory {
public:
    template <typename T>
    void registerType(const std::string& category) {
        auto typeIndex = std::type_index(typeid(T));
        creators[category][typeIndex] = []() -> std::shared_ptr<ComputeObject> {
            return std::make_shared<T>();
        };
    }

    std::shared_ptr<ComputeObject> create(const std::string& category, const std::type_index& typeIndex) {
        auto categoryIt = creators.find(category);
        if (categoryIt != creators.end()) {
            auto typeIt = categoryIt->second.find(typeIndex);
            if (typeIt != categoryIt->second.end()) {
                // Check if cached object exists
                if (cache.find(typeIndex) == cache.end()) {
                    cache[typeIndex] = typeIt->second(); // Instantiate and cache the object
                }
                // Use clone() to return a shared_ptr to a new instance
                return cache[typeIndex]->clone();
            }
        }
        return nullptr; // Type or category not registered
    }

    // Clear the cache if needed
    void clearCache() {
        cache.clear();
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::type_index, std::function<std::shared_ptr<ComputeObject>()>>> creators;

    // Cache for storing created instances using shared_ptr
    std::unordered_map<std::type_index, std::shared_ptr<ComputeObject>> cache;
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