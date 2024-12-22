#include <iostream>
#include <vector>
#include <unordered_map>

class SparseMatrix {
public:
    std::vector<int> row_indices;
    std::vector<int> col_indices;
    std::vector<double> values;

    SparseMatrix() {}

    void insert(int row, int col, double value) {
        if (value != 0) {
            row_indices.push_back(row);
            col_indices.push_back(col);
            values.push_back(value);
        }
    }

    void print() const {
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << "Element at (" << row_indices[i] << ", " << col_indices[i] << ") = " << values[i] << std::endl;
        }
    }
};

// Function to calculate the outer product of two sparse matrices
SparseMatrix outerProduct(const SparseMatrix &A, const SparseMatrix &B) {
    SparseMatrix C;

    // Use a hash map to accumulate results
    std::unordered_map<std::pair<int, int>, double, boost::hash<std::pair<int, int>>> result_map;

    // Outer product calculation
    for (size_t i = 0; i < A.values.size(); ++i) {
        for (size_t j = 0; j < B.values.size(); ++j) {
            // Calculate the product of non-zero elements
            int new_row = A.row_indices[i];
            int new_col = B.col_indices[j];
            double product = A.values[i] * B.values[j];

            if (result_map.find({new_row, new_col}) != result_map.end()) {
                // If already exists, accumulate the value
                result_map[{new_row, new_col}] += product;
            } else {
                // Otherwise, initialize it
                result_map[{new_row, new_col}] = product;
            }
        }
    }

    // Fill the sparse matrix C with accumulated results
    for (const auto &entry : result_map) {
        C.insert(entry.first.first, entry.first.second, entry.second);
    }

    return C;
}

int main() {
    SparseMatrix A, B;

    // Example sparse matrix A
    A.insert(0, 0, 1.0);
    A.insert(1, 0, 2.0);
    A.insert(1, 1, 3.0);

    // Example sparse matrix B
    B.insert(0, 0, 4.0);
    B.insert(0, 1, 5.0);
    B.insert(1, 0, 6.0);

    SparseMatrix C = outerProduct(A, B);

    std::cout << "Outer Product Result:" << std::endl;
    C.print();

    return 0;
}
