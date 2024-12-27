#include <iostream>
#include <chrono>

const int ARRAY_SIZE = 1000;
int array[ARRAY_SIZE][ARRAY_SIZE];

// Function without constraints
int sumArrayWithoutConstraints(int top_left_x, int top_left_y, int bottom_right_x, int bottom_right_y) {
    int sum = 0;
    for (int x = 0; x < ARRAY_SIZE; x++) {
        for (int y = 0; y < ARRAY_SIZE; y++) {
            if (x >= top_left_x && x <= bottom_right_x && y >= top_left_y && y <= bottom_right_y) {
                sum += array[x][y];
            }
        }
    }
    return sum;
}

// Function with necessity and sufficiency constraints
int sumArrayWithConstraints(int top_left_x, int top_left_y, int bottom_right_x, int bottom_right_y) {
    int sum = 0;
    for (int x = top_left_x; x <= bottom_right_x; x++) {
        for (int y = top_left_y; y <= bottom_right_y; y++) {
            sum += array[x][y];
        }
    }
    return sum;
}

int main() {
    // Initialise array (random values for demonstration)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            array[i][j] = rand() % 100;
        }
    }

    // Define subarray coordinates
    int top_left_x = 200;
    int top_left_y = 300;
    int bottom_right_x = 500;
    int bottom_right_y = 400;

    // Performance testing
    {
        auto start = std::chrono::high_resolution_clock::now();
        int result = sumArrayWithoutConstraints(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Sum without constraints: " << result << std::endl;
        std::cout << "Time taken without constraints: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        int result = sumArrayWithConstraints(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Sum with constraints: " << result << std::endl;
        std::cout << "Time taken with constraints: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }

    return 0;
}
