#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include <typeinfo>

// For polymorphic approach
#include <typeindex>
#include <unordered_map>

// Example data structures
struct MonomorphicData {
  int value;
  std::string name;

  template <typename Archive>
  void serialize(Archive& ar) {
    ar(value, name);
  }

  template <typename Archive>
  void deserialize(Archive& ar) {
    ar(value, name);
  }
};

// Base class for polymorphic data
struct PolymorphicDataBase {
  virtual ~PolymorphicDataBase() = default;

  template <typename Archive>
  void serialize(Archive& ar) {
    ar(static_cast<const std::type_info&>(typeid(*this)));
  }

  template <typename Archive>
  void deserialize(Archive& ar) {
    std::type_index type;
    ar(type);
    auto it = deserializationRegistry.find(type);
    if (it == deserializationRegistry.end()) {
      throw std::runtime_error("Unsupported type for deserialization");
    }
    it->second(*this, ar);
  }

  static std::unordered_map<std::type_index, std::function<void(PolymorphicDataBase&, std::istream&)>> deserializationRegistry;
};

std::unordered_map<std::type_index, std::function<void(PolymorphicDataBase&, std::istream&)>> PolymorphicDataBase::deserializationRegistry = {};

struct PolymorphicDataDerived1 : PolymorphicDataBase {
  int value;

  template <typename Archive>
  void serialize(Archive& ar) {
    PolymorphicDataBase::serialize(ar);
    ar(value);
  }

  template <typename Archive>
  void deserialize(Archive& ar) {
    PolymorphicDataBase::deserialize(ar);
    ar(value);
  }

  static void deserializeImpl(PolymorphicDataBase& base, std::istream& ar) {
    auto& derived = static_cast<PolymorphicDataDerived1&>(base);
    ar(derived.value);
  }
};

struct PolymorphicDataDerived2 : PolymorphicDataBase {
  std::string name;

  template <typename Archive>
  void serialize(Archive& ar) {
    PolymorphicDataBase::serialize(ar);
    ar(name);
  }

  template <typename Archive>
  void deserialize(Archive& ar) {
    PolymorphicDataBase::deserialize(ar);
    ar(name);
  }

  static void deserializeImpl(PolymorphicDataBase& base, std::istream& ar) {
    auto& derived = static_cast<PolymorphicDataDerived2&>(base);
    ar(derived.name);
  }
};

// Register deserialization functions for derived types
template <>
void PolymorphicDataBase::deserializationRegistry.emplace(std::type_index(typeid(PolymorphicDataDerived1)), &PolymorphicDataDerived1::deserializeImpl);

template <>
void PolymorphicDataBase::deserializationRegistry.emplace(std::type_index(typeid(PolymorphicDataDerived2)), &PolymorphicDataDerived2::deserializeImpl);

// Serialization/deserialization helpers
template <typename T>
void save(const T& data, std::ostream& os) {
  auto& ar = os;
  data.serialize(ar);
}

template <typename T>
void load(T& data, std::istream& is) {
  auto& ar = is;
  data.deserialize(ar);
}

// Performance test functions
template <typename T, typename Container>
void testPerformance(const Container& data, std::string testName) {
  std::stringstream ss;

  auto start = std::chrono::high_resolution_clock::now();
  for (const auto& entry : data) {
    save(entry, ss);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto serializationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  ss.seekg(0);

  Container deserializedData;
  start = std::chrono::high_resolution_clock::now();
  for (const auto& entry : data) {
    T temp;
    load(temp, ss);
    deserializedData.push_back(std::move(temp));
  }
  end = std::chrono::high_resolution_clock::now();
  auto deserializationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  std::cout << "Test: " << testName << std::endl;
  std::cout << "Serialization time: " << serializationTime << " us" << std::endl;
  std::cout << "Deserialization time: " << deserializationTime << " us" << std::endl;
  std::cout << "Total time: " << serializationTime + deserializationTime << " us" << std::endl;
  std::cout << std::endl;
}

int main() {
  const int numElements = 100000;

  std::vector<MonomorphicData> monomorphicData;
  std::vector<std::unique_ptr<PolymorphicDataBase>> polymorphicData;

  // Generate test data
  for (int i = 0; i < numElements; ++i) {
    MonomorphicData md{i, "test" + std::to_string(i)};
    monomorphicData.push_back(md);

    if (i % 2 == 0) {
      polymorphicData.push_back(std::make_unique<PolymorphicDataDerived1>(i));
    } else {
      polymorphicData.push_back(std::make_unique<PolymorphicDataDerived2>("test" + std::to_string(i)));
    }
  }

  testPerformance<MonomorphicData>(monomorphicData, "Monomorphic");
  testPerformance<std::unique_ptr<PolymorphicDataBase>>(polymorphicData, "Polymorphic");

  return 0;
}