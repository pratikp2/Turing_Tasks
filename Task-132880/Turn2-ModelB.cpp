int main() {
    DeploymentStrategy* basicStrategy = new BasicDeploymentStrategy();

    // Continuous deployment: Allow users to configure the deployment strategy dynamically
    std::string deploymentStrategyConfig = "Logging,Monitoring"; // User-configured

    DeploymentStrategy* decoratedStrategy = basicStrategy;
    for (const std::string& decorator : deploymentStrategyConfig) {
        if (decorator == "Logging") {
            decoratedStrategy = new LoggingDeploymentDecorator(decoratedStrategy);
        } else if (decorator == "Monitoring") {
            decoratedStrategy = new MonitoringDeploymentDecorator(decoratedStrategy);
        } // Add more decorators as needed
    }

    decoratedStrategy->deploy();

    // ...

    // Later, users can change the deployment strategy configuration
    deploymentStrategyConfig = "Logging,Rollback";
    // Recreate the decorated strategy based on the new configuration
    // ...

    return 0;
}
