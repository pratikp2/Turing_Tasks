#include <cstdio>
#include <cstring>

#define MAX_COMMANDS 10
#define MAX_STRING_LENGTH 100

// Enhanced version of the previous function to dynamically manage an array of strings
char** manageDynamicStringArray(const char** configStrings, size_t* numCommands) {
    char** stringArray = nullptr;

    // Ensure numCommands is non-null
    if (!numCommands) {
        fprintf(stderr, "numCommands pointer is null.\n");
        return nullptr;
    }

    // Check for negative number of commands
    if (*numCommands <= 0) {
        fprintf(stderr, "Number of commands must be positive.\n");
        return nullptr;
    }

    // Dynamically allocate memory for the string array
    stringArray = new char*[*numCommands];

    // Initialize each string in the array with a copy of the corresponding configuration string
    for (size_t i = 0; i < *numCommands; i++) {
        size_t stringLength = strlen(configStrings[i]) + 1;
        stringArray[i] = new char[stringLength];
        strcpy(stringArray[i], configStrings[i]);
    }

    return stringArray;
}

void updateStringInArray(char** stringArray, size_t index, const char* newString) {
    if (!stringArray) {
        fprintf(stderr, "stringArray pointer is null.\n");
        return;
    }

    if (index >= MAX_COMMANDS) {
        fprintf(stderr, "Index is out of bounds.\n");
        return;
    }

    size_t newStringLength = strlen(newString) + 1;
    // Deallocate the old string if it is different from the new string
    if (strcmp(stringArray[index], newString) != 0) {
        delete[] stringArray[index];
    }

    // Allocate memory for the new string
    stringArray[index] = new char[newStringLength];
    strcpy(stringArray[index], newString);
}

void freeDynamicStringArray(char** stringArray, size_t numCommands) {
    for (size_t i = 0; i < numCommands; i++) {
        delete[] stringArray[i];
    }
    delete[] stringArray;
}

int main() {
    const char* configStrings[] = {
        "MOVE 10 20",
        "TURN 45",
        "GRIP TRUE",
        "SPEED 75",
        "MOVE 20 30",
    };

    size_t numCommands = sizeof(configStrings) / sizeof(configStrings[0]);
    char** managedStrings = manageDynamicStringArray(configStrings, &numCommands);

    if (managedStrings) {
        // Display the initial configuration strings
        for (size_t i = 0; i < numCommands; i++) {
            printf("String [%zu]: %s\n", i, managedStrings[i]);
        }

        // Update a specific configuration string
        updateStringInArray(managedStrings, 2, "GRIP FALSE");

        // Display the updated configuration strings
        printf("\nConfiguration strings after update:\n");
        for (size_t i = 0; i < numCommands; i++) {
            printf("String [%zu]: %s\n", i, managedStrings[i]);
        }

        // Free the dynamically allocated memory
        freeDynamicStringArray(managedStrings, numCommands);
        printf("Memory freed successfully.\n");
    }

    return 0;
}
