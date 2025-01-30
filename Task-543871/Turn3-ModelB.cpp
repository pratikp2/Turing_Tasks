#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <string>
#include <typeinfo>

enum class ObjectCategory {
    ALGORITHM,
    DATA_PROCESSOR
};

// Base class for all compute-intensive objects
class ComputeObject {
public:
    virtual void compute() = 0;
    virtual ObjectCategory getCategory() const { return ObjectCategory::ALGORITHM; }
    virtual ~ComputeObject() = default;
};

// Derived classes for specific compute-intensive objects
class MatrixMultiplication : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Matrix Multiplication...\n";
    }
    ObjectCategory getCategory() const override { return ObjectCategory::ALGORITHM; }
};

class FourierTransform : public ComputeObject {
public:
    void compute() override {
        std::cout << "Computing Fourier Transform...\n";
    }
    ObjectCategory getCategory() const override { return ObjectCategory::ALGORITHM; }
};

class DataNormalizer : public ComputeObject {
public:
    void compute() override {
        std::cout << "Normalizing Data...\n";
    }
    ObjectCategory getCategory() const override { return ObjectCategory::DATA_PROCESSOR; }
};

// Factory class to handle dynamic object creation using RTTI
class ComputeObjectFactory {
public:
    using Creator = std::function<std::unique_ptr<ComputeObject>()>;
    
    template <typename T>
    void registerType(ObjectCategory category) {
        auto typeIndex = std::type_index(typeid(T));
        creators[typeIndex][category] = []() -> std::unique_ptr<ComputeObject> {
            return std::make_unique<T>();
        };
    }

    template <typename T>
    std::unique_ptr<ComputeObject> create(ObjectCategory category) {
        auto typeIndex = std::type_index(typeid(T));
        auto it = creators.find(typeIndex);
        if (it != creators.end() && it->second.find(category) != it->second.end()) {
            return it->second[category]();
        }
        return nullptr; // Type not registered
    }

    std::unique_ptr<ComputeObject> createByName(const std::string& typeName, ObjectCategory category) {
        const std::type_info& type = typeid(ComputeObject);
        for (const auto& entry : creators) {
            const std::type_info& registeredType = entry.first;
            if (strcmp(type.name(), registeredType.name()) == 0 &&
                entry.second.find(category) != entry.second.end()) {
                if (registeredType.name() == typeName.c_str()) {
                    return entry.second[category]();
                }
            }
        }
        return nullptr; // Type not found
    }

private:
    std::unordered_map<std::type_index, std::unordered_map<ObjectCategory, Creator>> creators;
};

// Example usage
int main() {
    ComputeObjectFactory factory;

    // Registering the types that can be created
    factory.registerType<MatrixMultiplication>(ObjectCategory::ALGORITHM);
    factory.registerType<FourierTransform>(ObjectCategory::ALGORITHM);
    factory.registerType<DataNormalizer>(ObjectCategory::DATA_PROCESSOR);

    // Creating objects dynamically by type using templated function
    auto matrixMultObj = factory.create<MatrixMultiplication>(ObjectCategory::ALGORITHM);
    if (matrixMultObj) {
        matrixMultObj->compute();
    }

    // Creating objects dynamically by type name
    std::string dataNormTypeName = typeid(DataNormalizer).name();
    auto dataNormObj = factory.createByName(dataNormTypeName, ObjectCategory::DATA_PROCESSOR);
    if (dataNormObj) {
        dataNormObj->compute();
    }

    return 0;
}
