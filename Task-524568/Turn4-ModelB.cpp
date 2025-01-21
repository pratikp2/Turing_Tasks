#include <iostream>

class SparseMatrix {
public:
    SparseMatrix(int rows, int cols);
    ~SparseMatrix();
    
    void insert(int row, int col, double value);
    double get(int row, int col) const;
    void remove(int row, int col);
    void display() const;

private:
    int rows;
    int cols;
    int nnz;
    int capacity;

    double* values;
    int* col_indices;
    int* row_ptr;

    // Array to keep track of valid elements
    bool* is_valid;

    void resize();
};

SparseMatrix::SparseMatrix(int rows, int cols)
    : rows(rows), cols(cols), nnz(0), capacity(2)
{
    values = new double[capacity];
    col_indices = new int[capacity];
    row_ptr = new int[rows + 1]{0};
    is_valid = new bool[capacity]{true};
}

SparseMatrix::~SparseMatrix() {
    delete[] values;
    delete[] col_indices;
    delete[] row_ptr;
    delete[] is_valid;
}

void SparseMatrix::resize() {
    capacity *= 2;
    double* new_values = new double[capacity];
    int* new_col_indices = new int[capacity];
    bool* new_is_valid = new bool[capacity]{true};

    for (int i = 0; i < nnz; ++i) {
        new_values[i] = values[i];
        new_col_indices[i] = col_indices[i];
        new_is_valid[i] = is_valid[i];
    }

    delete[] values;
    delete[] col_indices;
    delete[] is_valid;

    values = new_values;
    col_indices = new_col_indices;
    is_valid = new_is_valid;
}

void SparseMatrix::insert(int row, int col, double value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; i++) {
        if (col_indices[i] == col) {
            values[i] = value;
            is_valid[i] = true;  // Reuse existing element
            return;
        }
    }

    if (nnz >= capacity) {
        resize();
    }

    values[nnz] = value;
    col_indices[nnz] = col;
    is_valid[nnz] = true;
    nnz++;

    for (int i = row + 1; i <= rows; ++i) {
        row_ptr[i]++;
    }
}

double SparseMatrix::get(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col && is_valid[i]) {
            return values[i];
        }
    }

    return 0.0;
}

void SparseMatrix::remove(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Row or column index out of bounds");
    }

    for (int i = row_ptr[row]; i < row_ptr[row + 1]; ++i) {
        if (col_indices[i] == col && is_valid[i]) {
            is_valid[i] = false;
            return;
        }
    }
}

void SparseMatrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << get(i, j) << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    SparseMatrix sm(5, 5);

    sm.insert(0, 1, 3.14);
    sm.insert(1, 0, 2.71);
    sm.insert(3, 4, 6.28);
    sm.insert(4, 4, 1.41);
    sm.insert(4, 3, 4.19);

    std::cout << "Sparse matrix representation:\n";
    sm.display();

    std::cout << "Value at (0, 1): " << sm.get(0, 1) << "\n";

    sm.remove(4, 3); // Remove element (4, 3)

    std::cout << "\nSparse matrix after removing (4, 3):\n";
    sm.display();

    try {
        sm.get(-1, 0); // Trigger out-of-bounds exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
