#include <iostream>
#include "Matrix.h"

int main(){

    std::string file_name = "input.txt";
    Matrix matrix_1(Matrix::load_matrices_from_file(file_name)[0]);
    Matrix matrix_2(Matrix::load_matrices_from_file(file_name)[1]);
    Matrix matrix3 = matrix_1 + matrix_2;
    matrix_1.print_matrix();
    matrix_2.print_matrix();
    matrix3.print_matrix();
}