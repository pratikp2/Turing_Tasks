#include <iostream>
#include <ctime>
#include <cstdlib>

const int GRID_SIZE = 512;  // Size of the 3D grid
const int NUM_ITERATIONS = 100; // Number of iterations for each grid point

using namespace std;

// Function to perform intensive computation at each grid point
void computeIntensive(double* data, int x, int y, int z) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        double sum = 0.0;
        for (int j = 0; j < 100; ++j) {
            sum += pow(x, j) * pow(y, j) * pow(z, j);
        }
        *data = sum;
    }
}

int main() {
    double* dataGrid = new double[GRID_SIZE * GRID_SIZE * GRID_SIZE];

    cout << "====== WITH LOOP BOUNDS CHECKING ======" << endl;
    {
        // Measure time with loop bounds checking
        clock_t start = clock();
        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                for (int z = 0; z < GRID_SIZE; ++z) {
                    computeIntensive(dataGrid + x * GRID_SIZE * GRID_SIZE + y * GRID_SIZE + z, x, y, z);
                }
            }
        }
        clock_t end = clock();
        double time_elapsed = double(end - start) / CLOCKS_PER_SEC;

        cout << "Grid size: " << GRID_SIZE << endl;
        cout << "Time elapsed with bounds checking: " << time_elapsed << " seconds" << endl;
    }

    cout << "\n====== WITHOUT LOOP BOUNDS CHECKING ======" << endl;
    { 
        // Measure time without loop bounds checking (using inline assembly to toggle bounds checking)
        clock_t start = clock();

        // Toggle off loop bounds checking for the loops
        #ifdef __i386__  // For 32-bit architectures
        __asm__ volatile("pushf\n" "notl %%eax\n" "popf\n");
        #elif defined(__x86_64__) // For 64-bit architectures
        __asm__ volatile("pushfq\n" "notq %%rax\n" "popfq\n");
        #endif
 
        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                for (int z = 0; z < GRID_SIZE; ++z) {
                    computeIntensive(dataGrid + x * GRID_SIZE * GRID_SIZE + y * GRID_SIZE + z, x, y, z);                  
                }
            }
        }

        #ifdef __i386__  // For 32-bit architectures
        __asm__ volatile("pushf\n" "notl %%eax\n" "popf\n");
        #elif defined(__x86_64__) // For 64-bit architectures
        __asm__ volatile("pushfq\n" "notq %%rax\n" "popfq\n");
        #endif 
 
        clock_t end = clock();
        double time_elapsed = double(end - start) / CLOCKS_PER_SEC;

        cout << "Grid size: " << GRID_SIZE << endl;
        cout << "Time elapsed without bounds checking: " << time_elapsed << " seconds" << endl;
    }

    delete[] dataGrid;

    return 0;
}
