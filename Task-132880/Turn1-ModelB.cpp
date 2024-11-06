#include <iostream>

// Base DeploymentStrategy interface
class DeploymentStrategy {
public:
    virtual void deploy() = 0;
};

// Concrete DeploymentStrategy
class BasicDeploymentStrategy : public DeploymentStrategy {
public:
    void deploy() override {
        std::cout << "Deploying content using basic strategy..." << std::endl;
    }
};

// Decorator Base Class
class DeploymentDecorator : public DeploymentStrategy {
protected:
    DeploymentStrategy* decoratedStrategy;

public:
    DeploymentDecorator(DeploymentStrategy* strategy) : decoratedStrategy(strategy) {}
    void deploy() override {
        decoratedStrategy->deploy();
    }
};

// Logging Decorator
class LoggingDeploymentDecorator : public DeploymentDecorator {
public:
    LoggingDeploymentDecorator(DeploymentStrategy* strategy) : DeploymentDecorator(strategy) {}
    void deploy() override {
        std::cout << "Logging deployment start..." << std::endl;
        DeploymentDecorator::deploy();
        std::cout << "Logging deployment end..." << std::endl;
    }
};

// Monitoring Decorator
class MonitoringDeploymentDecorator : public DeploymentDecorator {
public:
    MonitoringDeploymentDecorator(DeploymentStrategy* strategy) : DeploymentDecorator(strategy) {}
    void deploy() override {
        std::cout << "Starting monitoring during deployment..." << std::endl;
        DeploymentDecorator::deploy();
        std::cout << "Stopping monitoring after deployment..." << std::endl;
    }
};

// Rollback Decorator
class RollbackDeploymentDecorator : public DeploymentDecorator {
public:
    RollbackDeploymentDecorator(DeploymentStrategy* strategy) : DeploymentDecorator(strategy) {}
    void deploy() override {
        std::cout << "Performing rollback in case of failure..." << std::endl;
        DeploymentDecorator::deploy();
    }
};

int main() {
    DeploymentStrategy* basicStrategy = new BasicDeploymentStrategy();
    basicStrategy->deploy(); // Output: Deploying content using basic strategy...

    // Decorate the basic strategy with logging and monitoring
    DeploymentStrategy* decoratedStrategy = new LoggingDeploymentDecorator(new MonitoringDeploymentDecorator(basicStrategy));
    decoratedStrategy->deploy();
    // Output:
    // Logging deployment start...
    // Starting monitoring during deployment...
    // Deploying content using basic strategy...
    // Stopping monitoring after deployment...
    // Logging deployment end...

    // Add rollback capability
    decoratedStrategy = new RollbackDeploymentDecorator(decoratedStrategy);
    decoratedStrategy->deploy();
    // Output:
    // Performing rollback in case of failure...
    // Logging deployment start...
    // Starting monitoring during deployment...
    // Deploying content using basic strategy...
    // Stopping monitoring after deployment...
    // Logging deployment end...

    delete decoratedStrategy;
    return 0;
}
