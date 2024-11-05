alignas(64) float positions[100000];
alignas(64) float velocities[100000];
struct RobotState {
	alignas(16) float position[3];
	alignas(16) float orientation[4];
	float velocity;
	float angularVelocity;
};
struct SimulationState {
	alignas(64) RobotState robots[100];
	alignas(64) float sensorData[1000];
	alignas(64) float controlInputs[100];
	// Other simulation data
};
