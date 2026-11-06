#include "old_main.h"

void Old_Matrix::print_matrix(const std::vector<std::vector<int>>& matrix, const std::string& name) {
    if (matrix.empty()) {
        std::cout << "\n" << name << " is empty." << std::endl;
        return;
    }
    std::cout << "\n" << name << ":" << std::endl;
    for (const auto& row : matrix) {
        for (int number : row) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>>* Old_Matrix::select_matrix(std::vector<std::vector<int>>& m1, std::vector<std::vector<int>>& m2) {
    char choice;
    std::cout << "Select Matrix (A/B): ";
    std::cin >> choice;
    if (choice == 'A' || choice == 'a') return &m1;
    if (choice == 'B' || choice == 'b') return &m2;
    std::cout << "Invalid choice! Defaulting to Matrix A." << std::endl;
    return &m1;
}

bool Old_Matrix::load_matrices_from_file(const std::string& file_name, std::vector<std::vector<int>>& m1, std::vector<std::vector<int>>& m2) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << file_name << "'!" << std::endl;
        return false;
    }

    m1.clear();
    m2.clear();

    int matrix_size = 0;
    if (!(file >> matrix_size)) {
        std::cerr << "Error: Could not read matrix size from file!" << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); 

    int line_count = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<int> matrix_line;
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
            matrix_line.push_back(std::stoi(token));
        }

        if (matrix_line.empty()) continue;
        line_count++;

        if (line_count <= matrix_size) {
            m1.push_back(matrix_line);
        } else {
            m2.push_back(matrix_line);
        }
    }

    std::cout << "\nSuccessfully loaded matrices from file!" << std::endl;
    return true;
}

std::vector<std::vector<int>> Old_Matrix::add_matrices(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2) {
    std::vector<std::vector<int>> result;
    if (m1.empty() || m2.empty()) return result;

    int rows1 = m1.size(), cols1 = m1[0].size();
    int rows2 = m2.size(), cols2 = m2[0].size();

    if (rows1 != rows2 || cols1 != cols2) {
        std::cerr << "\nError: Matrix addition requires identical dimensions!" << std::endl;
        return result;
    }

    for (int i = 0; i < rows1; i++) {
        std::vector<int> row;
        for (int j = 0; j < cols1; j++) {
            row.push_back(m1[i][j] + m2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Old_Matrix::multiply_matrices(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2) {
    std::vector<std::vector<int>> result;
    if (m1.empty() || m2.empty()) return result;

    int rows_A = m1.size(), cols_A = m1[0].size();
    int rows_B = m2.size(), cols_B = m2[0].size();

    if (cols_A != rows_B) {
        std::cerr << "\nError: Cannot multiply! Columns of A (" << cols_A 
             << ") must equal Rows of B (" << rows_B << ")." << std::endl;
        return result;
    }

    result.resize(rows_A, std::vector<int>(cols_B, 0));
    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            for (int k = 0; k < cols_A; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

void Old_Matrix::print_diagonals(const std::vector<std::vector<int>>& matrix, const std::string& name) {
    if (matrix.empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    int main_diag_sum = 0;
    int anti_diag_sum = 0;

    int n = std::min(rows, cols);
    for (int i = 0; i < n; i++) {
        main_diag_sum += matrix[i][i];
        anti_diag_sum += matrix[i][cols - 1 - i];
    }

    std::cout << "\n" << name << " Diagonals:" << std::endl;
    std::cout << "  Main Diagonal Sum: " << main_diag_sum << std::endl;
    std::cout << "  Anti-Diagonal Sum: " << anti_diag_sum << std::endl;
}

void Old_Matrix::swap_rows(std::vector<std::vector<int>>& matrix, int row1, int row2) {
    int total_rows = matrix.size();
    if (row1 < 0 || row1 >= total_rows || row2 < 0 || row2 >= total_rows) {
        std::cerr << "\nError: Invalid row indices (" << row1 << ", " << row2 << ")." << std::endl;
        return;
    }
    std::swap(matrix[row1], matrix[row2]);
    std::cout << "\nSuccessfully swapped Row " << row1 << " and Row " << row2 << "." << std::endl;
}

void Old_Matrix::swap_columns(std::vector<std::vector<int>>& matrix, int col1, int col2) {
    if (matrix.empty()) return;
    int total_cols = matrix[0].size();

    if (col1 < 0 || col1 >= total_cols || col2 < 0 || col2 >= total_cols) {
        std::cerr << "\nError: Invalid column indices (" << col1 << ", " << col2 << ")." << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix.size(); i++) {
        std::swap(matrix[i][col1], matrix[i][col2]);
    }
    std::cout << "\nSuccessfully swapped Column " << col1 << " and Column " << col2 << "." << std::endl;
}

void Old_Matrix::modify_element(std::vector<std::vector<int>>& matrix, int row, int col, int new_value) {
    if (matrix.empty()) {
        std::cerr << "\nError: Matrix is empty!" << std::endl;
        return;
    }

    int total_rows = matrix.size();
    int total_cols = matrix[0].size();

    if (row < 0 || row >= total_rows || col < 0 || col >= total_cols) {
        std::cerr << "\nError: Position (" << row << ", " << col << ") is out of bounds! "
             << "Valid range: Rows [0, " << total_rows - 1 << "], Cols [0, " << total_cols - 1 << "]." << std::endl;
        return;
    }

    int old_value = matrix[row][col];
    matrix[row][col] = new_value;

    std::cout << "\nSuccessfully updated position (" << row << ", " << col 
         << ") from " << old_value << " to " << new_value << "." << std::endl;
}

int old_main() {
    std::vector<std::vector<int>> matrix_1;
    std::vector<std::vector<int>> matrix_2;
    std::vector<std::vector<int>> matrix_3;

    std::string file_name;
    std::cout << "Please enter file name: ";
    std::cin >> file_name;

    if (!Old_Matrix::load_matrices_from_file(file_name, matrix_1, matrix_2)) {
        return 1;
    }

    int choice = 0;
    while (choice != 9) {
        std::cout << "\n====================================" << std::endl;
        std::cout << "       MATRIX OPERATIONS MENU       " << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "1. Display Matrix A and Matrix B" << std::endl;
        std::cout << "2. Add Matrices (C = A + B)" << std::endl;
        std::cout << "3. Multiply Matrices (C = A * B)" << std::endl;
        std::cout << "4. Calculate Diagonal Sums" << std::endl;
        std::cout << "5. Swap Rows in a Matrix" << std::endl;
        std::cout << "6. Swap Columns in a Matrix" << std::endl;
        std::cout << "7. Modify Element in a Matrix" << std::endl;
        std::cout << "8. Display Current Matrix C" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice (1-9): ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Old_Matrix::print_matrix(matrix_1, "Matrix A");
                Old_Matrix::print_matrix(matrix_2, "Matrix B");
                break;
            }
            case 2: {
                matrix_3 = Old_Matrix::add_matrices(matrix_1, matrix_2);
                Old_Matrix::print_matrix(matrix_3, "Matrix C (Addition Result)");
                break;
            }
            case 3: {
                matrix_3 = Old_Matrix::multiply_matrices(matrix_1, matrix_2);
                Old_Matrix::print_matrix(matrix_3, "Matrix C (Multiplication Result)");
                break;
            }
            case 4: {
                std::vector<std::vector<int>>* selected = Old_Matrix::select_matrix(matrix_1, matrix_2);
                std::string name = (selected == &matrix_1) ? "Matrix A" : "Matrix B";
                Old_Matrix::print_diagonals(*selected, name);
                break;
            }
            case 5: {
                std::vector<std::vector<int>>* selected = Old_Matrix::select_matrix(matrix_1, matrix_2);
                int r1, r2;
                std::cout << "Enter two 0-indexed row numbers to swap: ";
                std::cin >> r1 >> r2;
                Old_Matrix::swap_rows(*selected, r1, r2);
                break;
            }
            case 6: {
                std::vector<std::vector<int>>* selected = Old_Matrix::select_matrix(matrix_1, matrix_2);
                int c1, c2;
                std::cout << "Enter two 0-indexed column numbers to swap: ";
                std::cin >> c1 >> c2;
                Old_Matrix::swap_columns(*selected, c1, c2);
                break;
            }
            case 7: {
                std::vector<std::vector<int>>* selected = Old_Matrix::select_matrix(matrix_1, matrix_2);
                int r, c, val;
                std::cout << "Enter 0-indexed row and column to modify (e.g. 1 2): ";
                std::cin >> r >> c;
                std::cout << "Enter new integer value: ";
                std::cin >> val;
                Old_Matrix::modify_element(*selected, r, c, val);
                break;
            }
            case 8: {
                Old_Matrix::print_matrix(matrix_3, "Matrix C");
                break;
            }
            case 9: {
                std::cout << "\nExiting program. Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "\nInvalid choice! Please select an option between 1 and 9." << std::endl;
                break;
            }
        }
    }

    return 0;
}