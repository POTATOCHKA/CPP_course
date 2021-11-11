#include <gtest/gtest.h>

#include "Matrix_operations.h"

TEST(Func, Punct_1) {
    Matrix Matr = {{1, 2}, {3, 4}};
    EXPECT_EQ(Matr[0][1], 2);

    Array diag = Matr.get_diagonal();
    for (int i = 0; i < diag.get_size(); i++) {
        EXPECT_EQ(diag[i], Matr[i][i]);
    }

    int num_col = 0;
    Array stlb = Matr.get_column(num_col);
    for (int i = 0; i < Matr.get_num_of_rows(); i++) {
        EXPECT_EQ(stlb[i], Matr[i][num_col]);
    }

    int num_row = 1;
    Array strk = Matr.get_row(num_row);
    for (int i = 0; i < Matr.get_num_of_cols(); i++) {
        EXPECT_EQ(strk[i], Matr[num_row][i]);
    }
}

TEST(Func, Punct_2) {
    Array A = {1, 2};
    Array B = {3, 4};
    Matrix C = {A, B};

    Matrix D = {{1, 2}, {3, 4}};
}

TEST(Func, Punct_3) {
    Matrix A = {{1, 1, 1}, {1, 1, 1}};
    Matrix B = {{2, 2, 2}, {2, 2, 2}};
    Matrix C = B - A;
    for (int i = 0; i < C.get_num_of_rows(); i++) {
        for (int j = 0; j < C.get_num_of_cols(); j++) {
            EXPECT_EQ(C[i][j], A[i][j]);
        }
    }

    C = B * A;
    for (int i = 0; i < C.get_num_of_rows(); i++) {
        for (int j = 0; j < C.get_num_of_cols(); j++) {
            EXPECT_EQ(C[i][j], B[i][j]);
        }
    }

    C = B / A;
    for (int i = 0; i < C.get_num_of_rows(); i++) {
        for (int j = 0; j < C.get_num_of_cols(); j++) {
            EXPECT_EQ(C[i][j], B[i][j]);
        }
    }

    Matrix D = {{3, 3, 3}, {3, 3, 3}};
    C = A + B;
    for (int i = 0; i < C.get_num_of_rows(); i++) {
        for (int j = 0; j < C.get_num_of_cols(); j++) {
            EXPECT_EQ(C[i][j], D[i][j]);
        }
    }
}

TEST(Func, Punct_4) {
    Matrix A = {{1, 1},
                {1, 1}};
    A = A * 4;
    for (int i = 0; i < A.get_num_of_rows(); i++) {
        for (int j = 0; j < A.get_num_of_cols(); j++) {
            EXPECT_EQ(A[i][j], 4);
        }
    }

    Array B = {2, 2};
    Array B_check = {4, 4};
    Matrix T = {{1, 1},
                {1, 1}};
    B = B * T;
    for (int i = 0; i < B.get_size(); i++) {
        EXPECT_EQ(B_check[i], B[i]);
    }

    Matrix D = {{1}, {1}};
    Array K = {2, 2};
    D = D.dot(K);
    Matrix D_check = {{2, 2}, {2, 2}};
    for (int i = 0; i < A.get_num_of_rows(); i++) {
        for (int j = 0; j < A.get_num_of_cols(); j++) {
            EXPECT_EQ(D[i][j], D_check[i][j]);
        }
    }

    Matrix M1 = {{1, -1}, {2, 0}, {3, 0}};
    Matrix M2 = {{1, 1}, {2, 0}};
    Matrix check_M = {{-1, 1}, {2, 2}, {3, 3}};
    Matrix Prod = M1.dot(M2);
    for (int i = 0; i < check_M.get_num_of_rows(); i++) {
        for (int j = 0; j < check_M.get_num_of_cols(); j++) {
            EXPECT_EQ(Prod[i][j], check_M[i][j]);
        }
    }
}

TEST(Func, Punct_5) {
    Matrix B = {{2, 2}, {2, 2}};
    B = B + 3;
    Matrix check_B = {{5, 5}, {5, 5}};
    for (int i = 0; i < B.get_num_of_rows(); i++) {
        for (int j = 0; j < B.get_num_of_cols(); j++) {
            EXPECT_EQ(B[i][j], check_B[i][j]);
        }
    }

    Array A = {1, 1};
    A = A + 4;
    Array check_A = {5, 5};
    for (int i = 0; i < A.get_size(); i++) {
        EXPECT_EQ(check_A[i], A[i]);
    }

    Matrix D = {{1, 2}, {3, 4}};
    Array E = {1, 2};
    Matrix C = D.sum_with_arr(E, 0);
    Matrix C_check = {{2, 4}, {4, 6}};
    for (int i = 0; i < C_check.get_num_of_rows(); i++) {
        for (int j = 0; j < C_check.get_num_of_cols(); j++) {
            EXPECT_EQ(C[i][j], C_check[i][j]);
        }
    }

    Matrix F = D.sum_with_arr(E, 1);
    Matrix F_check = {{2, 3}, {5, 6}};
    for (int i = 0; i < F_check.get_num_of_rows(); i++) {
        for (int j = 0; j < F_check.get_num_of_cols(); j++) {
            EXPECT_EQ(F[i][j], F_check[i][j]);
        }
    }
}

TEST(Func, Punct_6) {
    Matrix A(5, 5);
    A.flatten();
    Matrix trans_A = A.Transpose();
    for (int i = 0; i < A.get_num_of_rows(); i++) {
        for (int j = 0; j < A.get_num_of_cols(); j++) {
            EXPECT_EQ(A[j][i], trans_A[i][j]);
        }
    }

    Matrix B = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
    B = B.inverse();
    Matrix check_B = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
    for (int i = 0; i < check_B.get_num_of_rows(); i++) {
        for (int j = 0; j < check_B.get_num_of_cols(); j++) {
            EXPECT_EQ(B[i][j], check_B[i][j]);
        }
    }
}

TEST(Func, Punct_7) {
    Matrix A = {{1, 2, 4}, {2, 1, 3}, {2, 2, 1}};
    int det = A.Determinant();
    int check_det = 11;
    EXPECT_EQ(check_det, det);
}
TEST(Func, Punct_8) {
    Matrix A = {{1, 2, 4, 5}, {2, 1, 3, 6}, {2, 2, 1, 7}};
    Matrix slice_A = A(make_pair(1, 3), make_pair(2, 4));
    Matrix check_slice_A = {{3, 6}, {1, 7}};
    for (int i = 0; i < check_slice_A.get_num_of_rows(); i++) {
        for (int j = 0; j < check_slice_A.get_num_of_cols(); j++) {
            EXPECT_EQ(slice_A[i][j], check_slice_A[i][j]);
        }
    }
}