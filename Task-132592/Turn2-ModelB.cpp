#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>

// Base class for all auditing rules
class AuditingRule {
public:
    virtual void audit(const std::map<std::string, int>& data) = 0;
    virtual ~AuditingRule() = default;
};

// Concrete auditing rules for specific data fields
class MaxValueAuditingRule : public AuditingRule {
public:
    void audit(const std::map<std::string, int>& data) override {
        if (data.count(fieldName)) {
            int value = data.at(fieldName);
            if (value > maxValue) {
                std::cout << "Value " << value << " in field '" << fieldName << "' is greater than the maximum allowed value: " << maxValue << std::endl;
            }
        } else {
            std::cout << "Field '" << fieldName << "' not found in the data." << std::endl;
        }
    }

    MaxValueAuditingRule(const std::string& field, int max) : fieldName(field), maxValue(max) {}

private:
    std::string fieldName;
    int maxValue;
};

class MinValueAuditingRule : public AuditingRule {
    // Similar implementation as MaxValueAuditingRule but for min value
};

// Manager class that handles auditing rules and data
class AuditingManager {
public:
    void addAuditingRule(std::unique_ptr<AuditingRule> rule) {
        auditingRules.push_back(std::move(rule));
    }

    void auditData(const std::map<std::string, int>& data) {
        for (const auto& rule : auditingRules) {
            rule->audit(data);
        }
    }

    // Function to handle new data fields dynamically
    void updateSchema(const std::vector<std::string>& newFields) {
        for (const std::string& field : newFields) {
            if (supportedFields.find(field) == supportedFields.end()) {
                std::cout << "New field '" << field << "' detected. Adding default auditing rules..." << std::endl;
                // Add default auditing rules for new fields (e.g., max value = 10000)
                addAuditingRule(std::make_unique<MaxValueAuditingRule>(field, 10000));
                supportedFields.insert(field);
            }
        }
    }

private:
    std::vector<std::unique_ptr<AuditingRule>> auditingRules;
    std::set<std::string> supportedFields;  // To keep track of fields with auditing rules
};

int main() {
    AuditingManager manager;

    // Initial schema and auditing rules
    manager.updateSchema({"age", "salary"});
    manager.addAuditingRule(std::make_unique<MaxValueAuditingRule>("age", 150));
    manager.addAuditingRule(std::make_unique<MinValueAuditingRule>("salary", 20000));

    // Real-time data auditing
    std::map<std::string, int> data1 = {{"age", 30}, {"salary", 35000}};
    manager.auditData(data1);

    // New data arrives with an additional field "location"
    std::map<std::string, int> data2 = {{"age", 40}, {"salary", 40000}, {"location", 1}};
    manager.auditData(data2);  // Output: Field 'location' not found in the data.

    // Update the schema to include the new "location" field
    manager.updateSchema({"location"});
    manager.auditData(data2);  // Output: Value 1 in field 'location' is greater than the maximum allowed value: 10000 (default rule)

    //