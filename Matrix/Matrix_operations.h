#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class Array;
class Matrix;

class Array {
   private:
    size_t size;
    double* arr;
    bool is_proxy = false;

   public:
    friend class Matrix;

    Array(int lenght, int value_for_fill = 0);
    Array(std::initializer_list<double> init_list);
    Array(double* init_arr, int lenght, bool proxy);
    Array(const Array& other);
    Array(Array&& other);
    void print_arr();
    size_t GetSize();
    double& operator[](int index);
    Array operator+(const double& other);
    Array operator-(const double& other);
    Array operator+(const Array& other);
    Array operator-(const Array& other);
    Array operator*(const Array& other);
    Array operator/(const Array& other);
    Array operator*(const double& other);
    Array operator*(Matrix& other);
    Array operator=(Array& other);
    Array& operator=(Array&& other);

    ~Array() {
        if (!is_proxy) {
            delete[] arr;
        }
    }
};

class Matrix {
   private:
    size_t rows;
    size_t cols;
    double** matr;

   public:
    friend class Array;

    enum Axis {
        Column,
        Row
    };

    Matrix(size_t num_rows, size_t num_cols, double value_for_fill = 0);
    Matrix(std::initializer_list<std::initializer_list<double>> init_list);
    Matrix(std::initializer_list<Array> init_list, Axis ax);
    Matrix(std::vector<std::vector<double>> init_vector);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);

    std::pair<int, int> GetShape();
    const int GetNumOfRows();
    const int GetNumOfCols();
    void PrintMatr();
    void flatten();
    Array GetRow(size_t num_row);
    Array GetColumn(int num_column);
    Array GetDiagonal();
    Array operator[](int index);
    Matrix operator+(const double& other);
    Matrix operator*(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator/(const Matrix& other);
    Matrix operator*(const double& other);
    Matrix operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix operator()(std::pair<int, int> strk, std::pair<int, int> stlb);
    Matrix SumWithArr(const Array& other, Axis ax);
    Matrix dot(const Matrix& other);
    Matrix dot(const Array& other);
    Matrix Transpose();
    double Determinant();
    Matrix inverse();
    Matrix getCofactor();

    ~Matrix() {
        for (size_t i = 0; i < rows; i++) {
            delete[] matr[i];
        }
        delete[] matr;
    }
};