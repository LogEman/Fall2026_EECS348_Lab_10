#include <vector>
#include <string>

class Matrix{

private:
    std::vector<std::vector<int>> data;
public:
    Matrix();
    Matrix(std::vector<std::vector<int>> matrix);

    static std::vector<Matrix> load_matrices_from_file(std::string& file_name);
    void print_matrix();

    Matrix operator+(const Matrix& other) const;
  

    void pushback_matrix(std::vector<int> line);
};