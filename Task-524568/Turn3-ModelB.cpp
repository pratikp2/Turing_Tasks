#include <iostream>
#include <vector>
#include <unordered_map>

class SparseMatrix {
public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols), nnz(0) {
        row_ptr.assign(rows + 1, 0);
    }
    
    ~SparseMatrix() = default;
    
    // Insert a value into the sparse matrix
    void insert(int row, int col, double value);
    
    // Update the value of an existing element in the sparse matrix
    void update(int row, int col, double value);
    
    // Access the value of an element in the sparse matrix
    double get(int row, int col) const;
    
private:
    int rows; // Number of rows
    int cols; // Number of columns
    int nnz;  // Number of non-zero entries
    
    std::vector<int> row_ptr;     // Row pointers
    std::vector<double> values;     // Non-zero values
    std::vector<int> col_indices; // Column indices

    void adjustRowPtr(int row, int shift);
};

void SparseMatrix::insert(int row, int col, double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return;
    }
    
    // Check if the element already exists
    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            update(row, col, value);
            return;
        }
    }

    // Add the new non-zero element
    values.push_back(value);
    col_indices.push_back(col);
    ++nnz;
    
    // Adjust row pointers for subsequent rows
    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i]++;
    }
}

void SparseMatrix::update(int row, int col, double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return;
    }

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            values[i] = value;
            return;
        }
    }

    // If the element does not exist, it's already handled in the insert method
}

double SparseMatrix::get(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cerr << "Error: Index out of bounds." << std::endl;
        return 0.0;
    }

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            return values[i];
        }
    }

    return 0.0; // Element not found, return 0
}

void SparseMatrix::adjustRowPtr(int row, int shift) {
    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i] += shift;
    }
}

int main() {
    SparseMatrix sm(5, 5);

    sm.insert(0, 1, 3.14);
    sm.insert(1, 0, 2.71);
    sm.insert(1, 3, 4.20);
    sm.insert(3, 4, 6.28);
    sm.insert(4, 4, 1.41);

    sm.update(1, 3, 5.20); // Update an existing value

    std::cout << "Element (1, 3) value: " << sm.get(1, 3) << std::endl;
    std::cout << "Element (4, 4) value: " << sm.get(4, 4) << std::endl;
    std::cout << "Element (2, 0) value: " << sm.get(2, 0) << std::endl; // Accessing a non-existent element

    return 0;
}
