enum Condition {
    MOTOR_TEMP_HIGH = 0b00000001,  // condition 1
    VIBRATION_EXCESSIVE = 0b00000010, // condition 2
    BEARING_FAULT = 0b00000100,   // condition 3
    LOW_OIL_PRESSURE = 0b00001000, // condition 4
    // Add more conditions as needed, each with a unique power of 2
};

int systemState = 0;

void setCondition(Condition cond) {
    systemState |= cond; // Set the corresponding bit to 1
}

void clearCondition(Condition cond) {
    systemState &= ~cond; // Clear the corresponding bit to 0
}

bool checkCondition(Condition cond) {
    return (systemState & cond) != 0; // Check if the corresponding bit is 1
}
 
int main() {
    // Initialize the system state (all conditions are off)
    systemState = 0;

    // Simulate setting some conditions asynchronously
    setCondition(MOTOR_TEMP_HIGH);  
    setCondition(VIBRATION_EXCESSIVE);
    
    // Check the states
    bool tempHigh = checkCondition(MOTOR_TEMP_HIGH);
    bool bearingFault = checkCondition(BEARING_FAULT);
    
    // Print the states
    printf("Motor Temperature High: %s\n", tempHigh ? "True" : "False");
    printf("Bearing Fault: %s\n", bearingFault ? "True" : "False");
    printf("Current System State: %x\n", systemState); // Will output e.g., 0x12 in hex (00000010 00000010 in binary)

    // Simulate clearing a condition asynchronously
    clearCondition(VIBRATION_EXCESSIVE);

    return 0;
}
