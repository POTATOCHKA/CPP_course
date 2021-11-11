#include "Matrix_operations.h"

void Array::print_arr() {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    cout << endl;
}
int Array::get_size() {
    return size;
}

double& Array::operator[](int index) {
    return arr[index];
}

Array Array::operator+(const double& other) {
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] + other;
    }
    return new_arr;
}

Array Array::operator+(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] + other.arr[i];
    }
    return new_arr;
}

Array Array::operator-(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] - other.arr[i];
    }
    return new_arr;
}

Array Array::operator*(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] * other.arr[i];
    }
    return new_arr;
}

Array Array::operator/(const Array& other) {
    assert(other.size == size);
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] / other.arr[i];
    }
    return new_arr;
}

Array Array::operator*(const double& other) {
    Array new_arr(size);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = arr[i] * other;
    }
    return new_arr;
}

Array Array::operator=(const Array& other) {
    if (this == &other) {
        return *this;
    }

    Array ans(size);
    for (int i = 0; i < size; i++) {
        ans[i] = arr[i];
    }
    return ans;
}
Array& Array::operator=(Array&& other) {
    size = other.size;
    for (int i = 0; i < size; i++) {
        arr[i] = other[i];
    }
    return *this;
}

Array Array::operator*(Matrix& other) {
    assert(size == other.rows);
    Array new_arr(other.cols);
    for (int j = 0; j < other.cols; j++) {
        for (int k = 0; k < size; k++) {
            new_arr[j] += arr[k] * other.matr[k][j];
        }
    }
    return new_arr;
}

void Matrix::print_matr() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

pair<int, int> Matrix::get_shape() {
    return make_pair(rows, cols);
}

const int Matrix::get_num_of_rows() {
    return rows;
}

const int Matrix::get_num_of_cols() {
    return cols;
}

void Matrix::flatten() {
    int k = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matr[i][j] = k;
            k++;
        }
    }
}

Array Matrix::get_row(int num_row) {
    assert(num_row < rows);
    Array new_arr(cols, 0);
    for (int j = 0; j < cols; ++j) {
        new_arr.arr[j] = matr[num_row][j];
    }
    return new_arr;
}

Array Matrix::get_column(int num_col) {
    assert(num_col < cols);
    Array new_arr(rows, 0);
    for (int i = 0; i < rows; ++i) {
        new_arr.arr[i] = matr[i][num_col];
    }
    return new_arr;
}

Array Matrix::get_diagonal() {
    int size = min(cols, rows);
    Array new_arr(size, 0);
    for (int i = 0; i < size; i++) {
        new_arr.arr[i] = matr[i][i];
    }
    return new_arr;
}

Array Matrix::operator[](int index) {
    Array temp(matr[index], cols, true);
    return temp;
}

Matrix Matrix::operator+(const double& other) {
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] + other;
        }
    }
    return new_matr;
}

Matrix Matrix::operator*(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] * other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator+(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] + other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator-(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] - other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator/(const Matrix& other) {
    assert(rows == other.rows && cols == other.cols);
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] / other.matr[i][j];
        }
    }
    return new_matr;
}

Matrix Matrix::operator*(const double& other) {
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            new_matr.matr[i][j] = matr[i][j] * other;
        }
    }
    return new_matr;
}

Matrix Matrix::operator()(pair<int, int> strk, pair<int, int> stlb) {
    assert(strk.first >= 0 && strk.second <= rows && stlb.first >= 0 && stlb.second <= cols);
    Matrix ans(strk.second - strk.first, stlb.second - stlb.first);
    int k = 0;
    int t = 0;
    for (int i = strk.first; i < strk.second; i++) {
        for (int j = stlb.first; j < stlb.second; j++) {
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ans[i][j] = matr[i][j];
        }
    }
    return ans;
}
Matrix& Matrix::operator=(Matrix&& other) {
    rows = other.rows;
    cols = other.cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matr[i][j] = other.matr[i][j];
        }
    }
    return *this;
}

Matrix Matrix::sum_with_arr(const Array& other, int axis = 0) {  // axis = 0 по столбцам, axis = 1 по строкам
    Matrix ans(rows, cols);
    if (axis == 0) {
        assert(other.size == cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ans[i][j] = matr[i][j] + other.arr[j];
            }
        }
    } else {
        assert(other.size == rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ans[i][j] = matr[i][j] + other.arr[i];
            }
        }
    }
    return ans;
}

Matrix Matrix::dot(const Matrix& other) {
    assert(cols == other.rows);
    Matrix new_matr(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < cols; k++) {
                new_matr[i][j] += matr[i][k] * other.matr[k][j];
            }
        }
    }
    return new_matr;
}

Matrix Matrix::dot(const Array& other) {
    assert(cols == 1);
    Matrix new_matr(rows, other.size);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.size; j++) {
            new_matr[i][j] += matr[i][0] * other.arr[j];
        }
    }
    return new_matr;
}

Matrix Matrix::Transpose() {
    Matrix new_matr(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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
    } else if (rows == 2) {
        det = (matr[0][0] * matr[1][1] - matr[0][1] * matr[1][0]);
        return det;
    } else {
        for (int p = 0; p < cols; p++) {
            vector<vector<double>> TempMatrix;
            for (int i = 1; i < rows; i++) {
                vector<double> TempRow;
                for (int j = 0; j < cols; j++) {
                    if (j != p) {
                        TempRow.push_back(matr[i][j]);
                    }
                }
                if (TempRow.size() > 0)
                    TempMatrix.push_back(TempRow);
            }
            Matrix newtempmatr = TempMatrix;
            det = det + matr[0][p] * pow(-1, p) * newtempmatr.Determinant();
        }
        return det;
    }
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
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            int p = 0;
            for (size_t x = 0; x < rows; x++) {
                if (x == i) {
                    continue;
                }
                int q = 0;

                for (size_t y = 0; y < rows; y++) {
                    if (y == j) {
                        continue;
                    }

                    subVect[p][q] = matr[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * subVect.Determinant();
        }
    }
    return solution;
}