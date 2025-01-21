#include <iostream>
#include <stdexcept>

class SparseMatrix {
public:
    SparseMatrix(int rows, int cols);
    ~SparseMatrix();
    
    // Method for adding or modifying elements
    void insert(int row, int col, double value);
    
    // Method for accessing an element
    double get(int row, int col) const;
    
    // Method for removing an element
    void remove(int row, int col);
    
    // Display the matrix
    void display() const;

private:
    int rows;          // Number of rows
    int cols;          // Number of columns
    int nnz;           // Number of non-zero entries
    int capacity;      // Maximum allocated memory space for non-zero entries

    double* values;    // Dynamic array for non-zero values
    int* col_indices;  // Dynamic array for column indices
    int* row_ptr;      // Dynamic array to point to the start of each row in values and col_indices

    void resize();
};

// Constructor
SparseMatrix::SparseMatrix(int rows, int cols)
    : rows(rows), cols(cols), nnz(0), capacity(2) // Start with a small capacity
{
    values = new double[capacity];
    col_indices = new int[capacity];
    row_ptr = new int[rows + 1]{0}; // Initializes all to 0
}

// Destructor
SparseMatrix::~SparseMatrix() {
    delete[] values;
    delete[] col_indices;
    delete[] row_ptr;
}

// Resize function
void SparseMatrix::resize() {
    capacity *= 2;
    double* new_values = new double[capacity];
    int* new_col_indices = new int[capacity];
    
    for (int i = 0; i < nnz; ++i) {
        new_values[i] = values[i];
        new_col_indices[i] = col_indices[i];
    }
    
    delete[] values;
    delete[] col_indices;
    
    values = new_values;
    col_indices = new_col_indices;
}

// Insert or modify an entry
void SparseMatrix::insert(int row, int col, double value) {
    // Check to prevent out-of-bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }
    
    // Check for existing elements in that row
    for (int i = row_ptr[row]; i < row_ptr[row + 1]; i++) {
        if (col_indices[i] == col) {
            values[i] = value; // Modify existing value
            return;
        }
    }

    // Need to add a new non-zero entry
    if (nnz >= capacity) {
        resize(); // Resize memory if capacity is exceeded
    }

    // Insert the new non-zero entry
    values[nnz] = value;
    col_indices[nnz] = col;
    nnz++;

    // Update the row_ptr
    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i]++;
    }
}

// Get the value at a specific position
double SparseMatrix::get(int row, int col) const {
    // Check to prevent out-of-bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }

    // Search for the value
    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            return values[i]; // Value found
        }
    }
    
    return 0.0; // Return zero if the value does not exist
}

// Remove an entry from the sparse matrix
void SparseMatrix::remove(int row, int col) {
    // Check to prevent out-of-bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }

    // Search for the value to remove
    int indexToDelete = -1;

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            indexToDelete = i;
            break;
        }
    }

    // If the entry does not exist, return
    if (indexToDelete == -1) {
        return; // Nothing to remove
    }

    // Shift elements down to remove
    for (int i = indexToDelete; i < nnz - 1; ++i) {
        values[i] = values[i + 1];
        col_indices[i] = col_indices[i + 1];
    }
    nnz--; // Decrement the count of non-zero entries

    // Update row_ptr accordingly
    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i]--;
    }

    // Clear the last element to prevent dangling access
    if (nnz < capacity / 4) { // Shrink the arrays if enough space is freed
        // Resize if necessary (optional)
        capacity /= 2;
        double* new_values = new double[capacity];
        int* new_col_indices = new int[capacity];
        
        for (int i = 0; i < nnz; ++i) {
            new_values[i] = values[i];
            new_col_indices[i] = col_indices[i];
        }
        
        delete[] values;
        delete[] col_indices;
        
        values = new_values;
        col_indices = new_col_indices;
    }
}

// Display the matrix
void SparseMatrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << "\n";
    }
}

// Example usage
int main() {
    SparseMatrix sm(5, 5);

    try {
        sm.insert(0, 1, 3.14);
        sm.insert(1, 0, 2.71);
        sm.insert(3, 4, 6.28);
        sm.insert(4, 4, 1.41);

        std::cout << "Sparse matrix representation:\n";
        sm.display();

        std::cout << "Value at (0, 1): " << sm.get(0, 1) << "\n";

        sm.insert(0, 1, 1.41); // Modify existing value
        std::cout << "Modified value at (0, 1): " << sm.get(0, 1) << "\n";

        sm.remove(0, 1); // Remove existing entry
        std::cout << "Value at (0, 1) after removal: " << sm.get(0, 1) << "\n";
        
        // This should throw an exception
        std::cout << "Accessing an out-of-bounds index: " << sm.get(5, 5) << "\n"; // This will throw

    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
