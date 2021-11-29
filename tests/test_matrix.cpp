#include <gtest/gtest.h>

#include "Matrix_operations.h"

TEST(Func, Test_indexing_diag_col_row) {
    Matrix Matr = {{1, 2}, {3, 4}};
    EXPECT_EQ(Matr[0][1], 2);

    Array diag = Matr.GetDiagonal();
    for (int i = 0; i < diag.GetSize(); i++) {
        EXPECT_EQ(diag[i], Matr[i][i]);
    }

    int num_col = 0;
    Array col = Matr.GetColumn(num_col);
    for (int i = 0; i < Matr.GetNumOfRows(); i++) {
        EXPECT_EQ(col[i], Matr[i][num_col]);
    }

    int num_row = 1;
    Array row = Matr.GetRow(num_row);
    for (int i = 0; i < Matr.GetNumOfCols(); i++) {
        EXPECT_EQ(row[i], Matr[num_row][i]);
    }
}

TEST(Func, Test_matrix_creating) {
    Array arr1= {1, 2};
    Array arr2 = {3, 4};
    Matrix matr1({arr1, arr2}, matr1.Row);

    Matrix right_matr1 = {{1, 2}, {3, 4}};
    for (int i = 0; i < right_matr1.GetNumOfRows(); i++) {
        for (int j = 0; j < right_matr1.GetNumOfCols(); j++) {
            EXPECT_EQ(matr1[i][j], right_matr1[i][j]);
        }
    }

    Matrix matr2({arr1, arr2}, matr2.Column);
    Matrix right_matr2 = {{1, 3}, {2, 4}};

    for (int i = 0; i < right_matr2.GetNumOfRows(); i++) {
        for (int j = 0; j < right_matr2.GetNumOfCols(); j++) {
            EXPECT_EQ(matr2[i][j], right_matr2[i][j]);
        }
    }

}

TEST(Func, Test_operations_on_elem) {
    Matrix matr1 = {{1, 1, 1}, {1, 1, 1}};
    Matrix matr2 = {{2, 2, 2}, {2, 2, 2}};
    Matrix res_matr = matr2 - matr1;
    for (int i = 0; i < res_matr.GetNumOfRows(); i++) {
        for (int j = 0; j < res_matr.GetNumOfCols(); j++) {
            EXPECT_EQ(res_matr[i][j], matr1[i][j]);
        }
    }

    res_matr = matr2 * matr1;
    for (int i = 0; i < res_matr.GetNumOfRows(); i++) {
        for (int j = 0; j < res_matr.GetNumOfCols(); j++) {
            EXPECT_EQ(res_matr[i][j], matr2[i][j]);
        }
    }

    res_matr = matr2 / matr1;
    for (int i = 0; i < res_matr.GetNumOfRows(); i++) {
        for (int j = 0; j < res_matr.GetNumOfCols(); j++) {
            EXPECT_EQ(res_matr[i][j], matr2[i][j]);
        }
    }

    Matrix sum_matr = {{3, 3, 3}, {3, 3, 3}};
    res_matr = matr1 + matr2;
    for (int i = 0; i < sum_matr.GetNumOfRows(); i++) {
        for (int j = 0; j < sum_matr.GetNumOfCols(); j++) {
            EXPECT_EQ(res_matr[i][j], sum_matr[i][j]);
        }
    }
}

TEST(Func, Test_operations_on_matr_arr) {
    Matrix matr1 = {{1, 1},
                {1, 1}};
    matr1 = matr1 * 4;
    for (int i = 0; i < matr1.GetNumOfRows(); i++) {
        for (int j = 0; j < matr1.GetNumOfCols(); j++) {
            EXPECT_EQ(matr1[i][j], 4);
        }
    }

    Array arr1 = {2, 2};
    Array right_arr1 = {4, 4};
    Matrix matr2 = {{1, 1},
                    {1, 1}};
    arr1 = arr1 * matr2;
    for (int i = 0; i < right_arr1.GetSize(); i++) {
        EXPECT_EQ(right_arr1[i], arr1[i]);
    }

    Matrix matr3 = {{1}, {1}};
    Array temp_arr = {2, 2};
    matr3 = matr3.dot(temp_arr);
    Matrix right_matr3 = {{2, 2}, {2, 2}};
    for (int i = 0; i < right_matr3.GetNumOfRows(); i++) {
        for (int j = 0; j < right_matr3.GetNumOfCols(); j++) {
            EXPECT_EQ(matr3[i][j], right_matr3[i][j]);
        }
    }

    Matrix matr4 = {{1, -1}, {2, 0}, {3, 0}};
    Matrix matr5 = {{1, 1}, {2, 0}};
    Matrix right_prod = {{-1, 1}, {2, 2}, {3, 3}};
    Matrix prod = matr4.dot(matr5);
    for (int i = 0; i < right_prod.GetNumOfRows(); i++) {
        for (int j = 0; j < right_prod.GetNumOfCols(); j++) {
            EXPECT_EQ(prod[i][j], right_prod[i][j]);
        }
    }
}

TEST(Func, Test_sum_arr_and_matr) {
    Matrix matr1 = {{2, 2}, {2, 2}};
    matr1 = matr1 + 3;
    Matrix check_matr1 = {{5, 5}, {5, 5}};
    for (int i = 0; i < check_matr1.GetNumOfRows(); i++) {
        for (int j = 0; j < check_matr1.GetNumOfCols(); j++) {
            EXPECT_EQ(matr1[i][j], check_matr1[i][j]);
        }
    }

    Array matr2 = {1, 1};
    matr2 = matr2 + 4;
    Array check_matr2 = {5, 5};
    for (int i = 0; i < check_matr2.GetSize(); i++) {
        EXPECT_EQ(check_matr2[i], matr2[i]);
    }

    Matrix matr3 = {{1, 2}, {3, 4}};
    Array temp_arr = {1, 2};
    Matrix sum_matr = matr3.SumWithArr(temp_arr, matr3.Column);
    Matrix check_sum_matr = {{2, 4}, {4, 6}};
    for (int i = 0; i < check_sum_matr.GetNumOfRows(); i++) {
        for (int j = 0; j < check_sum_matr.GetNumOfCols(); j++) {
            EXPECT_EQ(sum_matr[i][j], check_sum_matr[i][j]);
        }
    }

    Matrix sum_matr2 = matr3.SumWithArr(temp_arr, matr3.Row);
    Matrix check_sum_matr2 = {{2, 3}, {5, 6}};
    for (int i = 0; i < check_sum_matr2.GetNumOfRows(); i++) {
        for (int j = 0; j < check_sum_matr2.GetNumOfCols(); j++) {
            EXPECT_EQ(sum_matr2[i][j], check_sum_matr2[i][j]);
        }
    }
}

TEST(Func, Test_inv_matr) {
    Matrix matr1(5, 5);
    matr1.flatten();
    Matrix trans_matr1 = matr1.Transpose();
    for (int i = 0; i < matr1.GetNumOfRows(); i++) {
        for (int j = 0; j < matr1.GetNumOfCols(); j++) {
            EXPECT_EQ(trans_matr1[j][i], matr1[i][j]);
        }
    }

    Matrix matr2 = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
    matr2 = matr2.inverse();
    Matrix check_matr2 = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
    for (int i = 0; i < check_matr2.GetNumOfRows(); i++) {
        for (int j = 0; j < check_matr2.GetNumOfCols(); j++) {
            EXPECT_EQ(matr2[i][j], check_matr2[i][j]);
        }
    }
}

TEST(Func, Test_determinant) {
    Matrix matr1 = {{1, 2, 4}, {2, 1, 3}, {2, 2, 1}};
    int det = matr1.Determinant();
    int check_det = 11;
    EXPECT_EQ(check_det, det);
}

TEST(Func, Test_slice) {
    Matrix matr1 = {{1, 2, 4, 5}, {2, 1, 3, 6}, {2, 2, 1, 7}};
    Matrix slice_matr1 = matr1(std::make_pair(1, 3), std::make_pair(2, 4));
    Matrix check_slice_matr1 = {{3, 6}, {1, 7}};
    for (int i = 0; i < check_slice_matr1.GetNumOfRows(); i++) {
        for (int j = 0; j < check_slice_matr1.GetNumOfCols(); j++) {
            EXPECT_EQ(slice_matr1[i][j], check_slice_matr1[i][j]);
        }
    }
}