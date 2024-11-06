#include <iostream>
#include <string>

// Component Interface
class DeploymentStrategy {
public:
	virtual void deploy() = 0;
	virtual ~DeploymentStrategy() = default;
};

// Concrete Component
class BasicDeployment : public DeploymentStrategy {
public:
	void deploy() override {
		std::cout << "Performing basic deployment..." << std::endl;
	}
};

// Decorator Base Class
class DeploymentDecorator : public DeploymentStrategy {
protected:
	DeploymentStrategy* component;

public:
	DeploymentDecorator(DeploymentStrategy* component) : component(component) {}
	void deploy() override {
		component->deploy();
	}
	virtual ~DeploymentDecorator() = default;
};

// Concrete Decorators
class LoggingDeploymentDecorator : public DeploymentDecorator {
public:
	LoggingDeploymentDecorator(DeploymentStrategy* component) : DeploymentDecorator(component) {}
	void deploy() override {
		std::cout << "Logging deployment start:" << std::endl;
		DeploymentDecorator::deploy();
		std::cout << "Logging deployment end." << std::endl;
	}
};

class MonitoringDeploymentDecorator : public DeploymentDecorator {
public:
	MonitoringDeploymentDecorator(DeploymentStrategy* component) : DeploymentDecorator(component) {}
	void deploy() override {
		std::cout << "Enabling monitoring during deployment:" << std::endl;
		DeploymentDecorator::deploy();
		std::cout << "Disabling monitoring after deployment." << std::endl;
	}
};

int main() {
	DeploymentStrategy* basicDeployment = new BasicDeployment();

	std::cout << "Basic Deployment:" << std::endl;
	basicDeployment->deploy();

	DeploymentStrategy* deployedWithLogging = new LoggingDeploymentDecorator(basicDeployment);

	std::cout << "\nDeployment with Logging:" << std::endl;
	deployedWithLogging->deploy();

	DeploymentStrategy* deployedWithLoggingAndMonitoring = new MonitoringDeploymentDecorator(deployedWithLogging);

	std::cout << "\nDeployment with Logging and Monitoring:" << std::endl;
	deployedWithLoggingAndMonitoring->deploy();

	delete deployedWithLoggingAndMonitoring;
	delete deployedWithLogging;
	delete basicDeployment;
	return 0;
}
