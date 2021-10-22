#include <gtest/gtest.h>

extern "C" {
#include "all_functions.h"
}

TEST(Func, CreationTest) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head[] = "about c++";
    char body[] = "c++ is popular language";
    char *tags_arr[2];
    char str1[] = "c++";
    char str2[] = "cpp";
    tags_arr[0] = str1;
    tags_arr[1] = str2;

    create_post(&storage, head, body, 2, tags_arr, 12, 1, 2021);
    char *returned_head = get_head_of_post(&storage, 0);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(head[i], returned_head[i]);
    }
    char *returned_body = get_body_of_post(&storage, 0);
    for (int i = 0; i < 24; i++) {
        EXPECT_EQ(body[i], returned_body[i]);
    }
    EXPECT_EQ(2, get_num_of_tags(&storage, 0));
    char **returned_tags = get_tags_arr(&storage, 0);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(tags_arr[i][j], returned_tags[i][j]);
        }
    }
    int *date = get_date(&storage, 0);
    EXPECT_EQ(12, date[0]);
    EXPECT_EQ(1, date[1]);
    EXPECT_EQ(2021, date[2]);
}

TEST(Func, AddingComments) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head[] = "about c++";
    char body[] = "c++ is popular language";
    char *tags_arr[2];
    char str1[] = "c++";
    char str2[] = "cpp";
    tags_arr[0] = str1;
    tags_arr[1] = str2;

    create_post(&storage, head, body, 2, tags_arr, 12, 1, 2021);
    char *comments[2];
    char str3[] = "cool";
    char str4[] = "nice";
    comments[0] = str3;
    comments[1] = str4;
    int *date_of_comments[2];
    int date1[] = {22, 10, 2021};
    int date2[] = {7, 10, 2021};
    date_of_comments[0] = date1;
    date_of_comments[1] = date2;
    add_comment(&storage, 0, 2, comments, date_of_comments);
    char **returned_comments = get_comments(&storage, 0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(returned_comments[i][j], comments[i][j]);
        }
    }
    int **returned_dates = get_dates_of_comment(&storage, 0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(returned_dates[i][j], date_of_comments[i][j]);
        }
    }
}
TEST(Func, AddingRates) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head[] = "about c++";
    char body[] = "c++ is popular language";
    char *tags_arr[2];
    char str1[] = "c++";
    char str2[] = "cpp";
    tags_arr[0] = str1;
    tags_arr[1] = str2;

    create_post(&storage, head, body, 2, tags_arr, 12, 1, 2021);
    int scores[] = {5, 4, 5};
    add_rate(&storage, 0, 3, scores);
    int *returned_scores = get_scores(&storage, 0);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(returned_scores[i], scores[i]);
    }
}
TEST(Func, PrintMostPost) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head[] = "about c++";
    char body[] = "c++ is popular language";
    char *tags_arr[2];
    char str1[] = "c++";
    char str2[] = "cpp";
    tags_arr[0] = str1;
    tags_arr[1] = str2;
    create_post(&storage, head, body, 2, tags_arr, 12, 1, 2021);

    char head1[] = "about python";
    char body1[] = "c++ is a nice language";
    char *tags_arr1[2];
    char str11[] = "python";
    char str12[] = "numpy";
    tags_arr1[0] = str11;
    tags_arr1[1] = str12;
    create_post(&storage, head1, body1, 2, tags_arr1, 23, 1, 2021);

    char *comments[2];
    char str3[] = "cool";
    char str4[] = "nice";
    comments[0] = str3;
    comments[1] = str4;
    int *date_of_comments[2];
    int date1[] = {22, 1, 2021};
    int date2[] = {7, 2, 2021};
    date_of_comments[0] = date1;
    date_of_comments[1] = date2;
    add_comment(&storage, 0, 2, comments, date_of_comments);

    char *comments2[2];
    char str5[] = "okey";
    char str6[] = "and?";
    comments2[0] = str5;
    comments2[1] = str6;
    int *date_of_comments2[2];
    int date3[] = {22, 1, 2021};
    int date4[] = {24, 1, 2021};
    date_of_comments2[0] = date3;
    date_of_comments2[1] = date4;
    add_comment(&storage, 0, 2, comments2, date_of_comments2);

    int result[] = {0};
    int i = 0;
    find_post_with_high_comm(&storage);
    int *returned_result = find_post_with_high_comm(&storage);
    bool all_arr_printed = false;
    returned_result[i] == -100;
    while (!all_arr_printed) {
        if (returned_result[i] == -100) {
            all_arr_printed = true;
        } else {
            EXPECT_EQ(returned_result[i], result[i]);
            i++;
        }
    }
}
