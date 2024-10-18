#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Base class for all auditing rules
class AuditingRule {
public:
  virtual void audit(const std::map<std::string, std::any> &data) = 0;
  virtual ~AuditingRule() = default;
};

// Concrete auditing rules for specific data fields
class RangeAuditingRule : public AuditingRule {
public:
  void audit(const std::map<std::string, std::any> &data) override {
    if (auto it = data.find(fieldName); it != data.end()) {
      int value = std::any_cast<int>(it->second);
      if (value < minValue || value > maxValue) {
        std::cout << "Value for '" << fieldName << "' is outside the range ["
                  << minValue << ", " << maxValue << "]" << std::endl;
      }
    }
  }

  RangeAuditingRule(const std::string &field, int min, int max)
      : fieldName(field), minValue(min), maxValue(max) {}

private:
  std::string fieldName;
  int minValue;
  int maxValue;
};

// Manager class that holds auditing rules and applies them
class AuditingManager {
public:
  void addAuditingRule(std::unique_ptr<AuditingRule> rule) {
    auditingRules.push_back(std::move(rule));
  }

  void auditData(const std::map<std::string, std::any> &data) {
    for (const auto &rule : auditingRules) {
      rule->audit(data);
    }
  }

private:
  std::vector<std::unique_ptr<AuditingRule>> auditingRules;
};

// Class to manage the dynamic schema
class SchemaManager {
public:
  void addField(const std::string &fieldName, DataType dataType) {
    schema[fieldName] = dataType;
  }

  DataType getDataType(const std::string &fieldName) const {
    if (auto it = schema.find(fieldName); it != schema.end()) {
      return it->second;
    }
    return DataType::Invalid;
  }

private:
  std::map<std::string, DataType> schema;