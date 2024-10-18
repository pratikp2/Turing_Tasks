#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>

// Base class for all auditing rules
class AuditingRule {
public:
  virtual void audit(const std::map<std::string, std::any>& data) = 0;
  virtual ~AuditingRule() = default;
};

// Concrete auditing rules
class MinMaxAuditingRule : public AuditingRule {
public:
  void audit(const std::map<std::string, std::any>& data) override {
    const std::string& fieldName = "value";

    if (data.find(fieldName) != data.end()) {
      int value = std::any_cast<int>(data[fieldName]);
      if (value < minValue || value > maxValue) {
        std::cout << "Value " << value << " in field '" << fieldName << "' is outside the range [" << minValue << ", " << maxValue << "]" << std::endl;
      }
    } else {
      std::cout << "Field '" << fieldName << "' not found in data for auditing." << std::endl;
    }
  }

  MinMaxAuditingRule(int min, int max) : minValue(min), maxValue(max) {}

private:
  int minValue;
  int maxValue;
};

class ExistenceAuditingRule : public AuditingRule {
public:
  void audit(const std::map<std::string, std::any>& data) override {
    if (data.find(requiredField) == data.end()) {
      std::cout << "Field '" << requiredField << "' is missing in the data." << std::endl;
    }
  }

  ExistenceAuditingRule(const std::string& field) : requiredField(field) {}

private:
  std::string requiredField;
};

// Manager class
class AuditingManager {
public:
  void addAuditingRule(std::unique_ptr<AuditingRule> rule) {
    auditingRules.push_back(std::move(rule));
  }

  void auditData(const std::map<std::string, std::any>& data) {
    for (const auto& rule : auditingRules) {
      rule->audit(data);
    }
  }

private:
  std::vector<std::unique_ptr<AuditingRule>> auditingRules;
};

int main() {
  AuditingManager manager;

  // Initial set of auditing rules
  manager.addAuditingRule(std::make_unique<MinMaxAuditingRule>(0, 100));
  manager.addAuditingRule(std::make_unique<ExistenceAuditingRule>("timestamp"));

  // Simulate receiving data
  std::map<std::string, std::any> data1{
    {"value", 50},
    {"timestamp", std::string("2023-07-31T10:00:00")}
  };
  manager.auditData(data1);

  std::map<std::string, std::any> data2{
    {"value", 150},
    // "timestamp" field is missing
  };
  manager.auditData(data2);

  // **Dynamically adding a new rule for a new field**
  std::string newField = "user_id";
  manager.addAuditingRule(std::make_unique<ExistenceAuditingRule>(newField));

  std::map<std::string, std::any> data3{
    {"value", 25},
    {"timestamp", std::string("2023-08-01T12:15:00")},
    {"user_id", 42}
  };
  manager.auditData(data3); // Will now audit for the existence of "user_id"

  return 0;
}