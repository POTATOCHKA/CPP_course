#include "Matrix_operations.h"

Array::Array(int lenght, int value_for_fill) {
    size = lenght;
    assert(size >= 1);
    arr = new double[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = value_for_fill;
    }
}

Array::Array(std::initializer_list<double> init_list) {
    size = init_list.size();
    assert(size >= 1);
    arr = new double[size];
    size_t index = 0;
    for (const auto& elem : init_list) {
        arr[index++] = elem;
    }
}

Array::Array(double* init_arr, int lenght, bool proxy) {
    is_proxy = proxy;  // proxy - флаг, который показывает нужно ли чистить память при удалении
                       // массива постороенного на основе динамического массива
    size = lenght;
    assert(size >= 1);
    arr = init_arr;
}

Array::Array(const Array& other) : size(other.size) {
    arr = new double[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

Array::Array(Array&& other) : arr(other.arr), size(other.size) {
    other.arr = nullptr;
    other.size = 0;
}

void Array::print_arr() {
    for (size_t i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << std::endl;
}
size_t Array::GetSize() {
    return size;
}

double& Array::operator[](int index) {
    assert(index >= 0 && index < size);
    return arr[index];
}

Array Array::operator+(const double& other) {
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] + other;
    }
    return new_arr;
}
Array Array::operator-(const double& other) {
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] - other;
    }
    return new_arr;
}

Array Array::operator+(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] + other.arr[i];
    }
    return new_arr;
}

Array Array::operator-(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] - other.arr[i];
    }
    return new_arr;
}

Array Array::operator*(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] * other.arr[i];
    }
    return new_arr;
}

Array Array::operator/(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] / other.arr[i];
    }
    return new_arr;
}

Array Array::operator*(const double& other) {
    Array new_arr(size);
    for (size_t i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] * other;
    }
    return new_arr;
}

Array Array::operator=(Array& other) {
    std::swap(this->size, other.size);
    std::swap(this->arr, other.arr);
    return *this;
}
Array& Array::operator=(Array&& other) {
    size = other.size;
    for (size_t i = 0; i < size; i++) {
        arr[i] = other[i];
    }
    return *this;
}

Array Array::operator*(Matrix& other) {
    assert(size == other.rows);
    Array new_arr(other.cols);
    for (size_t j = 0; j < other.cols; j++) {
        for (size_t k = 0; k < size; k++) {
            new_arr[j] += arr[k] * other.matr[k][j];
        }
    }
    return new_arr;
}

Matrix::Matrix(size_t num_rows, size_t num_cols, double value_for_fill) {
    rows = num_rows;
    cols = num_cols;
    assert(cols >= 1 && rows >= 1);
    matr = new double*[rows];
    for (size_t i = 0; i < rows; i++) {
        matr[i] = new double[cols];
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matr[i][j] = value_for_fill;
        }
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init_list) {
    rows = init_list.size();
    cols = init_list.begin()->size();
    for (const auto& vec : init_list) {
        assert(cols == vec.size());
    }
    matr = new double*[rows];
    for (size_t i = 0; i < rows; i++) {
        matr[i] = new double[cols];
    }
    int i = 0;
    int j = 0;
    for (const auto& vec : init_list) {
        for (const auto& el : vec) {
            matr[i][j] = el;
            j = (j + 1) % cols;
        }
        i = (i + 1) % rows;
    }
}

Matrix::Matrix(std::initializer_list<Array> init_list, Axis ax) {
    rows = init_list.size();
    cols = init_list.begin()->size;
    if (ax == Row) {
        for (const auto& vec : init_list) {
            assert(cols == vec.size);
        }
        matr = new double*[rows];
        for (size_t i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        int i = 0;
        for (const auto& vec : init_list) {
            for (size_t j = 0; j < vec.size; ++j) {
                matr[i][j] = vec.arr[j];
            }
            i = (i + 1) % rows;
        }
    } else {
        for (const auto& vec : init_list) {
            assert(rows == vec.size);
        }
        matr = new double*[cols];
        for (size_t i = 0; i < rows; i++) {
            matr[i] = new double[rows];
        }
        int j = 0;
        for (const auto& vec : init_list) {
            for (size_t i = 0; i < vec.size; ++i) {
                matr[i][j] = vec.arr[i];
            }
            j = (j + 1) % cols;
        }
    }
}

Matrix::Matrix(std::vector<std::vector<double>> init_vector) {
    rows = init_vector.size();
    cols = init_vector[0].size();
    assert(cols >= 1 && rows >= 1);
    matr = new double*[rows];
    for (size_t i = 0; i < rows; i++) {
        matr[i] = new double[cols];
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matr[i][j] = init_vector[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    matr = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matr[i] = new double[cols];
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matr[i][j] = other.matr[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& other) : rows(other.rows), cols(other.cols) {
    matr = other.matr;
    other.matr = nullptr;
    other.rows = 0;
    other.cols = 0;
}

void Matrix::PrintMatr() {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << matr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::pair<int, int> Matrix::GetShape() {
    return std::make_pair(rows, cols);
}

const int Matrix::GetNumOfRows() {
    return rows;
}

const int Matrix::GetNumOfCols() {
    return cols;
}

void Matrix::flatten() {
    int k = 0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matr[i][j] = k;
            k++;
        }
    }
}

Array Matrix::GetRow(size_t num_row) {
    assert(num_row < rows);
    Array new_arr(cols, 0);
    for (size_t j = 0; j < cols; ++j) {
        new_arr.arr[j] = matr[num_row][j];
    }
    return new_arr;
}

Array Matrix::GetColumn(int num_col) {
    assert(num_col < cols);
    Array new_arr(rows, 0);
    for (size_t i = 0; i < rows; ++i) {
        new_arr.arr[i] = matr[i][num_col];
    }
    return new_arr;
}

Array Matrix::GetDiagonal() {
    size_t size = std::min(cols, rows);
    Array new_arr(size, 0);
    for (size_t i = 0; i < size; i++) {
        new_arr[i] = matr[i][i];
    }
    return new_arr;
}

Array Matrix::operator[](int index) {
    assert(index >= 0 && index < rows);
    Array temp(matr[index], cols, true);
    return temp;
}

Matrix Matrix::operator+(const double& other) {
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] + other;
        }
    }
    return new_matr;
}

Matrix Matrix::operator*(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] * other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator+(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] + other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator-(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] - other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator/(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] / other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator*(const double& other) {
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] * other;
        }
    }
    return new_matr;
}

Matrix Matrix::operator()(std::pair<int, int> strk, std::pair<int, int> stlb) {
    assert(strk.first >= 0 && strk.second <= rows && stlb.first >= 0 && stlb.second <= cols);
    Matrix ans(strk.second - strk.first, stlb.second - stlb.first);
    int k = 0;
    int t = 0;
    for (size_t i = strk.first; i < strk.second; i++) {
        for (size_t j = stlb.first; j < stlb.second; j++) {
            ans[k][t] = matr[i][j];
            t++;
            t %= ans.cols;
        }
        k++;
        k %= ans.rows;
    }
    return ans;
}

Matrix Matrix::operator=(const Matrix& other) {
    Matrix ans(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            ans[i][j] = matr[i][j];
        }
    }
    return ans;
}
Matrix& Matrix::operator=(Matrix&& other) {
    rows = other.rows;
    cols = other.cols;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matr[i][j] = other.matr[i][j];
        }
    }
    return *this;
}

Matrix Matrix::SumWithArr(const Array& other, Axis ax) {
    Matrix ans(rows, cols);
    if (ax == Column) {
        assert(other.size == cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ans[i][j] = matr[i][j] + other.arr[j];
            }
        }
    } else {
        assert(other.size == rows);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ans[i][j] = matr[i][j] + other.arr[i];
            }
        }
    }
    return ans;
}

Matrix Matrix::dot(const Matrix& other) {
    assert(cols == other.rows);
    Matrix new_matr(rows, other.cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < other.cols; j++) {
            for (size_t k = 0; k < cols; k++) {
                new_matr[i][j] += matr[i][k] * other.matr[k][j];
            }
        }
    }
    return new_matr;
}

Matrix Matrix::dot(const Array& other) {
    assert(cols == 1);
    Matrix new_matr(rows, other.size);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < other.size; j++) {
            new_matr[i][j] += matr[i][0] * other.arr[j];
        }
    }
    return new_matr;
}

Matrix Matrix::Transpose() {
    Matrix new_matr(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            new_matr.matr[j][i] = matr[i][j];
        }
    }
    return new_matr;
}

double Matrix::Determinant() {
    assert(rows == cols);
    double det = 0;
    if (rows == 1) {
        return matr[0][0];
    }
    if (rows == 2) {
        det = (matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0]);
        return det;
    }
    for (size_t p = 0; p < cols; p++) {
        std::vector<std::vector<double>> TempMatrix;
        for (size_t i = 1; i < rows; i++) {
            std::vector<double> TempRow;
            for (int j = 0; j < cols; j++) {
                if (j != p) {
                    TempRow.push_back(matr[i][j]);
                }
            }
            if (TempRow.size() > 0) {
                TempMatrix.push_back(TempRow);
            }
        }
        Matrix newtempmatr = TempMatrix;
        det = det + matr[0][p] * pow(-1, p) * newtempmatr.Determinant();
    }
    return det;
}

Matrix Matrix::inverse() {
    double det = this->Determinant();
    assert(det != 0);

    double d = 1.0 / det;
    Matrix solution(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            solution[i][j] = matr[i][j];
        }
    }

    solution = solution.getCofactor();
    solution = solution.Transpose();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            solution[i][j] *= d;
        }
    }

    return solution;
}

Matrix Matrix::getCofactor() {
    assert(rows == cols);
    Matrix solution(rows, cols);
    Matrix subVect(rows - 1, cols - 1);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            int sub_row = 0;
            for (size_t x = 0; x < rows; x++) {
                if (x == i) {
                    continue;
                }
                int sub_col = 0;

                for (size_t y = 0; y < rows; y++) {
                    if (y == j) {
                        continue;
                    }

                    subVect[sub_row][sub_col] = matr[x][y];
                    sub_col++;
                }
                sub_row++;
            }
            solution[i][j] = pow(-1, i + j) * subVect.Determinant();
        }
    }
    return solution;
}