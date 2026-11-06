#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

class Old_Matrix {
public:
    static void print_matrix(const std::vector<std::vector<int>>& matrix, const std::string& name);
    static std::vector<std::vector<int>>* select_matrix(std::vector<std::vector<int>>& m1, std::vector<std::vector<int>>& m2);
    static bool load_matrices_from_file(const std::string& file_name, std::vector<std::vector<int>>& m1, std::vector<std::vector<int>>& m2);
    static std::vector<std::vector<int>> add_matrices(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2);
    static std::vector<std::vector<int>> multiply_matrices(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2);
    static void print_diagonals(const std::vector<std::vector<int>>& matrix, const std::string& name);
    static void swap_rows(std::vector<std::vector<int>>& matrix, int row1, int row2);
    static void swap_columns(std::vector<std::vector<int>>& matrix, int col1, int col2);
    static void modify_element(std::vector<std::vector<int>>& matrix, int row, int col, int new_value);
};