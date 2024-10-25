#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <functional>

// Base class for all computations
class Computation {
public:
  virtual double compute(double x) = 0;
  virtual ~Computation() = default;
};

// Concrete computation classes (extensible parts)
class Addition : public Computation {
public:
  double compute(double x) override {
    return x + 10.0;
  }
};

class Multiplication : public Computation {
public:
  double compute(double x) override {
    return x * 2.0;
  }
};

// Class to manage computations and perform lazy evaluation
class ComputationManager {
public:
  void registerComputation(const std::string& name, std::unique_ptr<Computation> computation) {
    computations[name] = std::move(computation);
  }

  double compute(const std::string& name, double x) {
    auto it = computations.find(name);
    if (it == computations.end()) {
      throw std::runtime_error("Computation not found");
    }

    // Lazy evaluation: Compute the result only when needed
    return it->second->compute(x);
  }

private:
  std::map<std::string, std::unique_ptr<Computation>> computations;
};

int main() {
  ComputationManager manager;
  manager.registerComputation("add", std::make_unique<Addition>());
  manager.registerComputation("mul", std::make_unique<Multiplication>());

  double input = 5.0;

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
      double result = manager.compute("add", input);
      result = manager.compute("mul", result);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken without lazy evaluation: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
  }

  // Let's create a lazy evaluated computation
  class LazyComputation : public Computation {
  public:
    LazyComputation(std::function<double(double)> func) : func(std::move(func)) {}
    double compute(double x) override {
      if (!result.has_value()) {
        result = func(x);
      }
      return *result;
    }

  private:
    std::function<double(double)> func;
    std::optional<double> result;
  };

  // Usage:
  manager.registerComputation("lazy_mul_add", std::make_unique<LazyComputation>([](double x) {
    return manager.compute("mul", manager.compute("add", x));
  }));

  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
      double result = manager.compute("lazy_mul_add", input);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken with lazy evaluation: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
  }

  return 0;
}