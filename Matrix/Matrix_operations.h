#include <assert.h>

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

class Array;
class Matrix;

class Array {
   private:
    int size;
    double* arr;
    bool is_proxy = false;

   public:
    friend class Matrix;

    Array(int lenght, int value_for_fill = 0) {
        size = lenght;
        assert(size >= 1);
        arr = new double[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = value_for_fill;
        }
    }

    Array(initializer_list<double> init_list) {
        size = int(init_list.size());
        assert(size >= 1);
        arr = new double[size];
        int temp = 0;
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            arr[temp] = *it;
            temp++;
        }
    }

    Array(double* init_arr, int lenght, bool proxy) {
        is_proxy = proxy;  // proxy - флаг, который показывает нужно ли чистить память при удалении
                           // массива постороенного на основе динамического массива
        size = lenght;
        assert(size >= 1);
        arr = init_arr;
    }

    Array(const Array& other) : size(other.size) {
        arr = new double[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    Array(Array&& other) : size(other.size) {
        arr = other.arr;
        other.arr = nullptr;
        other.size = 0;
    }

    void print_arr();
    int get_size();
    double& operator[](int index);
    Array operator+(const double& other);
    Array operator+(const Array& other);
    Array operator-(const Array& other);
    Array operator*(const Array& other);
    Array operator/(const Array& other);
    Array operator*(const double& other);
    Array operator*(Matrix& other);
    Array operator=(const Array& other);
    Array& operator=(Array&& other);

    ~Array() {
        if (!is_proxy) {
            delete[] arr;
        }
    }
};

class Matrix {
   private:
    int rows;
    int cols;
    double** matr;

   public:
    friend class Array;

    Matrix(int num_rows, int num_cols, double value_for_fill = 0) {
        rows = num_rows;
        cols = num_cols;
        assert(cols >= 1 && rows >= 1);
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matr[i][j] = value_for_fill;
            }
        }
    }

    Matrix(initializer_list<initializer_list<double>> init_list) {
        rows = int(init_list.size());
        cols = int(init_list.begin()->size());
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            assert(cols == it->size());
        }
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        int i = 0;
        int j = 0;
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                matr[i][j] = *it2;
                j = (j + 1) % cols;
            }
            i = (i + 1) % rows;
        }
    }

    Matrix(initializer_list<Array> init_list) {
        rows = int(init_list.size());
        cols = int(init_list.begin()->size);
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            assert(cols == it->size);
        }
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        int i = 0;
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            for (int j = 0; j < it->size; ++j) {
                matr[i][j] = it->arr[j];
            }
            i = (i + 1) % rows;
        }
    }

    Matrix(vector<vector<double>> init_vector) {
        rows = init_vector.size();
        cols = init_vector[0].size();
        assert(cols >= 1 && rows >= 1);
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matr[i][j] = init_vector[i][j];
            }
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols];
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matr[i][j] = other.matr[i][j];
            }
        }
    }

    Matrix(Matrix&& other) : rows(other.rows), cols(other.cols) {
        matr = other.matr;
        other.matr = nullptr;
        other.rows = 0;
        other.cols = 0;
    }

    pair<int, int> get_shape();
    const int get_num_of_rows();
    const int get_num_of_cols();
    void print_matr();
    void flatten();
    Array get_row(int num_row);
    Array get_column(int num_column);
    Array get_diagonal();
    Array operator[](int index);
    Matrix operator+(const double& other);
    Matrix operator*(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator/(const Matrix& other);
    Matrix operator*(const double& other);
    Matrix operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix operator()(pair<int, int> strk, pair<int, int> stlb);
    Matrix sum_with_arr(const Array& other, int axis);
    Matrix dot(const Matrix& other);
    Matrix dot(const Array& other);
    Matrix Transpose();
    double Determinant();
    Matrix inverse();
    void adjoint();
    Matrix getCofactor();

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] matr[i];
        }
        delete[] matr;
    }
};