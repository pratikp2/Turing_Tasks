#include <stdio.h>

enum Command {
    CMD_START,
    CMD_STOP,
    CMD_PAUSE,
    CMD_RESUME,
    CMD_UNKNOWN // For capturing unexpected commands
};

// Function to handle commands
void handleCommand(enum Command cmd) {
    // Switch statement to handle different commands
    switch (cmd) {
        case CMD_START:
            // Start the process
            printf("Starting the process...\n");
            break;

        case CMD_STOP:
            // Stop the process
            printf("Stopping the process...\n");
            break;

        case CMD_PAUSE:
            // Pause the process
            printf("Pausing the process...\n");
            break;

        case CMD_RESUME:
            // Resume the process
            printf("Resuming the process...\n");
            break;

        default:
            // Handle unknown commands
            printf("Unknown command received!\n");
            break;
    }
}

int main() {
    handleCommand(CMD_START);
    handleCommand(CMD_UNKNOWN); // Edge case, should trigger the default case
    return 0;
}
