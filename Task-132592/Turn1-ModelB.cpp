#include <iostream>
#include <memory>
#include <vector>

// Base class for all auditing rules
class AuditingRule {
public:
  virtual void audit(int data) = 0;
  virtual ~AuditingRule() = default;
};

// Concrete auditing rules (different strategies)
class RangeAuditingRule : public AuditingRule {
public:
  void audit(int data) override {
    if (data < minValue || data > maxValue) {
      std::cout << "Value " << data << " is outside the range [" << minValue
                << ", " << maxValue << "]" << std::endl;
    }
  }

  RangeAuditingRule(int min, int max) : minValue(min), maxValue(max) {}

private:
  int minValue;
  int maxValue;
};

class ValueAuditingRule : public AuditingRule {
public:
  void audit(int data) override {
    if (data == targetValue) {
      std::cout << "Value " << data << " matches the target value "
                << targetValue << std::endl;
    }
  }

  ValueAuditingRule(int target) : targetValue(target) {}

private:
  int targetValue;
};

// Manager class that holds auditing rules and applies them
class AuditingManager {
public:
  void addAuditingRule(std::unique_ptr<AuditingRule> rule) {
    auditingRules.push_back(std::move(rule));
  }

  void auditData(int data) {
    for (const auto &rule : auditingRules) {
      rule->audit(data);
    }
  }

private:
  std::vector<std::unique_ptr<AuditingRule>> auditingRules;
};

int main() {
  AuditingManager manager;

  // Adding auditing rules dynamically using late binding
  manager.addAuditingRule(std::make_unique<RangeAuditingRule>(0, 100));
  manager.addAuditingRule(std::make_unique<ValueAuditingRule>(42));

  // Real-time data auditing
  manager.auditData(50);  // Output: Value 50 is within the range [0, 100]
  manager.auditData(42);  // Output: Value 42 matches the target value 42
  manager.auditData(150); // Output: Value 150 is outside the range [0, 100]

  return 0;
}