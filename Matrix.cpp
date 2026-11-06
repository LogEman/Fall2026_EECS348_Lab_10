#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "old_main.h"

Matrix::Matrix(){

}
Matrix::Matrix(std::vector<std::vector<int>> matrix){
    std::vector<std::vector<int>> data = matrix;
}

void Matrix::pushback_matrix(std::vector<int> line){
    data.push_back(line);
}

Matrix Matrix::operator+(const Matrix& other) const {
    Old_Matrix::print_matrix(data, "Test1");
    Old_Matrix::print_matrix(other.data, "Test2");
    Old_Matrix::print_matrix(Old_Matrix::add_matrices(data, other.data), "Test3");
    return Matrix(Old_Matrix::add_matrices(data, other.data));
}

void Matrix::print_matrix(){
    if (data.empty()) {
        std::cout << "Matrix is empty." << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (int number : row) {
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Matrix> Matrix::load_matrices_from_file(std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << file_name << "'!" << std::endl;
        return {}; 
    }

    std::vector<Matrix> matrixArray;
    std::string matrix_size_string;
    
    // Read the single size header at the very top of the file
    if (!std::getline(file, matrix_size_string)) {
        return {};
    }

    int matrix_size = std::stoi(matrix_size_string);
    
    std::string line;
    Matrix currentMatrix;
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

        // Add the line to the current matrix first
        currentMatrix.pushback_matrix(matrix_line);
        line_count++;

        // Once we have reached the expected number of rows for this matrix
        if (line_count == matrix_size) {
            matrixArray.push_back(currentMatrix); // Save it
            currentMatrix = Matrix();             // Reset for the next matrix
            line_count = 0;                       // Reset row counter
        }
    }

    return matrixArray;
}

