#include <iostream>
#include <vector>

class SparseMatrix {
public:
    SparseMatrix(int rows, int cols);
    ~SparseMatrix();

    // Inserting a value into the sparse matrix
    void insert(int row, int col, double value);
    
    // Accessing a value from the sparse matrix
    double get(int row, int col) const;

    // Display the matrix
    void display() const;

private:
    int rows; // Number of rows
    int cols; // Number of columns
    int nnz;  // Number of non-zero entries

    std::vector<double> values;       // Non-zero values
    std::vector<int> col_indices;     // Column indices
    std::vector<int> row_ptr;         // Row pointer
};

SparseMatrix::SparseMatrix(int rows, int cols) : rows(rows), cols(cols), nnz(0) {
    row_ptr.resize(rows + 1, 0);
}

SparseMatrix::~SparseMatrix() {}

void SparseMatrix::insert(int row, int col, double value) {
    // Check for duplicate entries and replace the value if necessary
    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            values[i] = value;
            return;
        }
    }

    // Insert new non-zero element
    int position = nnz++;
    values.push_back(value);
    col_indices.push_back(col);

    // Update row_ptr
    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i]++;
    }

    // Add current nnz (after increment) to current row's position in row_ptr
    row_ptr[row + 1] = position + 1;
}

double SparseMatrix::get(int row, int col) const {
    // Searching for the value
    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col) {
            return values[i];
        }
    }
    return 0.0; // Return zero if not found
}

void SparseMatrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    SparseMatrix sm(5, 5);
    sm.insert(0, 1, 3.14);
    sm.insert(1, 0, 2.71);
    sm.insert(3, 4, 6.28);
    sm.insert(4, 4, 1.41);

    std::cout << "Sparse matrix representation:" << std::endl;
    sm.display();
    
    return 0;
}
