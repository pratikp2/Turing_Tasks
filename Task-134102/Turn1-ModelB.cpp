// Example of a lazy-evaluated rule engine

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>

class Sensor {
public:
    double getTemperature() const { return temperature; }
    double getHumidity() const { return humidity; }

    void update(double temperature, double humidity) {
        this->temperature = temperature;
        this->humidity = humidity;
    }

private:
    double temperature;
    double humidity;
};

class Rule {
public:
    using Condition = std::function<bool()>;
    using Action = std::function<void()>;

    Rule(Condition condition, Action action) : condition(condition), action(action) {}

    void evaluate() {
        if (condition()) {
            action();
        }
    }

private:
    Condition condition;
    Action action;
};

class RuleEngine {
public:
    void addRule(Rule rule) {
        rules.push_back(rule);
    }

    void evaluateRules() {
        for (const Rule& rule : rules) {
            rule.evaluate();
        }
    }

private:
    std::vector<Rule> rules;
};

int main() {
    Sensor sensor;
    RuleEngine ruleEngine;

    // Define the rules
    Rule rule1([&sensor] { return sensor.getTemperature() < 20.0; },
               [] { std::cout << "Heater turned on!" << std::endl; });

    Rule rule2([&sensor] { return sensor.getHumidity() > 60.0; },
               [] { std::cout << "Fan turned on!" << std::endl; });

    ruleEngine.addRule(rule1);
    ruleEngine.addRule(rule2);

    // Simulate sensor readings and evaluate the rules
    std::thread sensorThread([&sensor, &ruleEngine] {
        while (true) {
            // Simulate sensor readings
            double temperature = 25.0 + std::rand() % 10;
            double humidity = 50.0 + std::rand() % 10;
            sensor.update(temperature, humidity);

            // Evaluate the rules lazily
            ruleEngine.evaluateRules();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });