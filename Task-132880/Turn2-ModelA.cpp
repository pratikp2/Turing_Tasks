#include <vector>

 int main() {
	DeploymentStrategy* basicStrategy = new BasicDeploymentStrategy();

	std::vector<DeploymentStrategy*> decorators;

	// Runtime configuration: enable logging and monitoring
	decorators.push_back(new LoggingDeploymentDecorator(nullptr));
	decorators.push_back(new MonitoringDeploymentDecorator(nullptr));

	DeploymentStrategy* decoratedStrategy = basicStrategy;
	for (auto it = decorators.rbegin(); it != decorators.rend(); ++it) {
		(*it)->decoratedStrategy = decoratedStrategy;
		decoratedStrategy = *it;
	}

	decoratedStrategy->deploy();
	
	// Runtime configuration: Add rollback
	decorators.push_back(new RollbackDeploymentDecorator(nullptr));
	for (auto it = decorators.rbegin(); it != decorators.rend(); ++it) {
		if ((*it)->decoratedStrategy == nullptr) {
			(*it)->decoratedStrategy = decoratedStrategy;
			decoratedStrategy = *it;
			break;
		}
	}

	std::cout << "\nAfter adding rollback:\n";
	decoratedStrategy->deploy();

	// Cleanup
	for (auto decorator : decorators) {
		delete decorator;
	}
	delete basicStrategy;
	return 0;
}
