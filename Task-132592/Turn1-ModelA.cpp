#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Base class for auditors
class Auditor {
public:
  virtual void audit(const std::string &data) = 0;
  virtual ~Auditor() = default;
};

// Example concrete auditor classes (different types of auditors can be added
// later)
class LengthAuditor : public Auditor {
public:
  void audit(const std::string &data) override {
    if (data.length() > 10) {
      std::cout << "LengthAuditor: Data exceeds maximum length: " << data
                << std::endl;
    }
  }
};

class ContentAuditor : public Auditor {
public:
  void audit(const std::string &data) override {
    if (data.find("sensitive") != std::string::npos) {
      std::cout << "ContentAuditor: Sensitive content found: " << data
                << std::endl;
    }
  }
};

// Factory class to create auditors using late binding
class AuditorFactory {
public:
  std::unique_ptr<Auditor> createAuditor(const std::string &type) {
    auto creator = auditorCreators.find(type);
    if (creator == auditorCreators.end()) {
      throw std::runtime_error("Invalid auditor type: " + type);
    }
    return creator->second();
  }

  template <typename T> void registerAuditor(const std::string &type) {
    auditorCreators[type] = []() { return std::make_unique<T>(); };
  }

private:
  std::map<std::string, std::function<std::unique_ptr<Auditor>()>>
      auditorCreators;
};

int main() {
  AuditorFactory auditorFactory;

  // Register auditor types at runtime using late binding
  auditorFactory.registerAuditor<LengthAuditor>("Length");
  auditorFactory.registerAuditor<ContentAuditor>("Content");

  std::vector<std::unique_ptr<Auditor>> auditors;

  // Configuration-driven selection of auditors
  std::vector<std::string> auditorTypes = {"Length", "Content"};
  for (const std::string &type : auditorTypes) {
    auditors.push_back(auditorFactory.createAuditor(type));
  }

  // Real-time data processing and auditing
  std::string data = "This is a test message";
  for (const std::unique_ptr<Auditor> &auditor : auditors) {
    auditor->audit(data);
  }

  data = "This is a very long and sensitive message";
  for (const std::unique_ptr<Auditor> &auditor : auditors) {
    auditor->audit(data);
  }
  return 0;
}