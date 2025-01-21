#include <iostream>
#include <vector>

class SparseMatrix {
private:
    int rows;
    int cols;
    size_t num_non_zeros;

    // Pointers to the dynamically allocated arrays for COO format
    int* row_indices;
    int* col_indices;
    double* values;

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols), num_non_zeros(0) {
        // Initialize pointers with nullptr
        row_indices = nullptr;
        col_indices = nullptr;
        values = nullptr;
    }

    ~SparseMatrix() {
        delete[] row_indices;
        delete[] col_indices;
        delete[] values;
    }

    // Copy constructor
    SparseMatrix(const SparseMatrix& other) : rows(other.rows), cols(other.cols), num_non_zeros(other.num_non_zeros) {
        row_indices = new int[num_non_zeros];
        col_indices = new int[num_non_zeros];
        values = new double[num_non_zeros];

        for (size_t i = 0; i < num_non_zeros; ++i) {
            row_indices[i] = other.row_indices[i];
            col_indices[i] = other.col_indices[i];
            values[i] = other.values[i];
        }
    }
    
    // Move constructor
    SparseMatrix(SparseMatrix&& other) : rows(other.rows), cols(other.cols), num_non_zeros(other.num_non_zeros) {
        row_indices = other.row_indices;
        col_indices = other.col_indices;
        values = other.values;
        other.row_indices = nullptr;
        other.col_indices = nullptr;
        other.values = nullptr;
        other.num_non_zeros = 0;
    }

    // Copy assignment operator
    SparseMatrix& operator=(const SparseMatrix& other) {
        if (this != &other) {
            delete[] row_indices;
            delete[] col_indices;
            delete[] values;

            rows = other.rows;
            cols = other.cols;
            num_non_zeros = other.num_non_zeros;

            row_indices = new int[num_non_zeros];
            col_indices = new int[num_non_zeros];
            values = new double[num_non_zeros];

            for (size_t i = 0; i < num_non_zeros; ++i) {
                row_indices[i] = other.row_indices[i];
                col_indices[i] = other.col_indices[i];
                values[i] = other.values[i];
            }
        }
        return *this;
    }

    // Move assignment operator
    SparseMatrix& operator=(SparseMatrix&& other) {
        if (this != &other) {
            delete[] row_indices;
            delete[] col_indices;
            delete[] values;

            rows = other.rows;
            cols = other.cols;
            num_non_zeros = other.num_non_zeros;

            row_indices = other.row_indices;
            col_indices = other.col_indices;
            values = other.values;

            other.row_indices = nullptr;
            other.col_indices = nullptr;
            other.values = nullptr;
            other.num_non_zeros = 0;
        }
        return *this;
    }
    
    // Function to add a non-zero element to the matrix
    void insert(int row, int col, double value) {
        // Check if element is already present and value is different
        if (has_element(row, col)) {
            // Find the index of the existing element and update its value
            for (size_t i = 0; i < num_non_zeros; ++i) {
                if (row_indices[i] == row && col_indices[i] == col) {
                    values[i] = value;
                    return;
                }
            }
        }

        // Reallocate memory if we need more space for new elements
        if (num_non_zeros == sizeof(row_indices) / sizeof(int)) {
            reallocate_memory();
        }

        // Add the new element
        row_indices[num_non_zeros] = row;
        col_indices[num_non_zeros] = col;
        values[num_non_zeros] = value;
        ++num_non_zeros;
    }

    double get_element(int row, int col) const {
        for (size_t i = 0; i < num_non_zeros; ++i) {
            if (row_indices[i] == row && col_indices[i] == col) {
                return values[i];
            }
        }
        return 0.0;
    }

    // Check if a specific element exists in the sparse matrix
    bool has_element(int row, int col) const {
        for (size_t i = 0; i < num_non_zeros; ++i) {
            if (row_indices[i] == row && col_indices[i] == col) {
                return true;
            }
        }
        return false;
    }

    size_t num_elements() const {
        return num_non_zeros;
    }

    int num_rows() const {
        return rows;
    }

    int num_cols() const {
        return cols;
    }

private:
    // Function to reallocate memory when the matrix becomes full
    void reallocate_memory() {
        size_t new_size = 2 * (sizeof(row_indices) / sizeof(int));
        int* new_row_indices = new int[new_size];
        int* new_col_indices = new int[new_size];
        double* new_values = new double[new_size];

        for (size_t i = 0; i < num_non_zeros; ++i) {
            new_row_indices[i] = row_indices[i];
            new_col_indices[i] = col_indices[i];
            new_values[i] = values[i];
        }

        delete[] row_indices;
        delete[] col_indices;
        delete[] values;

        row_indices = new_row_indices;
        col_indices = new_col_indices;
        values = new_values;
    }
};

int main() {
    SparseMatrix sparseMatrix(4, 5);

    sparseMatrix.insert(0, 1, 1.2);
    sparseMatrix.insert(1, 2, 3.4);
    sparseMatrix.insert(2, 3, 5.6);
    sparseMatrix.insert(3, 0, 7.8);

    std::cout << "Number of elements: " << sparseMatrix.num_elements() << std::endl;

    double elementValue = sparseMatrix.get_element(1, 2);
    std::cout << "Element (1, 2): " << elementValue << std::endl;