#include <gtest/gtest.h>

extern "C" {
#include "Post_creator.h"
}

TEST(Func, CreationTest) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head_post1[] = "about c++";
    char body_post1[] = "c++ is popular language";
    const char *tags_arr_post1[] = {"c++", "cpp"};
    int creating_day_post1 = 12;
    int creating_month_post1 = 1;
    int creating_year_post1 = 2021;
    int num_tags_post1 = 2;
    create_post(&storage, head_post1, body_post1, num_tags_post1, tags_arr_post1, creating_day_post1, creating_month_post1, creating_year_post1);

    char *returned_head = get_head_of_post(&storage, 0);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(head_post1[i], returned_head[i]);
    }
    char *returned_body = get_body_of_post(&storage, 0);
    for (int i = 0; i < 24; i++) {
        EXPECT_EQ(body_post1[i], returned_body[i]);
    }
    EXPECT_EQ(num_tags_post1, get_num_of_tags(&storage, 0));
    char **returned_tags = get_tags_arr(&storage, 0);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(tags_arr_post1[i][j], returned_tags[i][j]);
        }
    }
    struct Date creation_date = get_date(&storage, 0);
    EXPECT_EQ(creating_day_post1, creation_date.day);
    EXPECT_EQ(creating_month_post1, creation_date.month);
    EXPECT_EQ(creating_year_post1, creation_date.year);
}

TEST(Func, AddingComments) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head_post1[] = "about c++";
    char body_post1[] = "c++ is popular language";
    const char *tags_arr_post1[] = {"c++", "cpp"};
    int creating_day_post1 = 12;
    int creating_month_post1 = 1;
    int creating_year_post1 = 2021;
    int num_tags_post1 = 2;
    create_post(&storage, head_post1, body_post1, num_tags_post1, tags_arr_post1, creating_day_post1, creating_month_post1, creating_year_post1);

    const char *comments_post1[] = {"cool++", "nice"};
    int num_comments_post1 = 2;
    struct Date date_of_comm1 = {22, 10, 2021};
    struct Date date_of_comm2 = {8, 10, 2021};
    struct Date date_of_comments[] = {date_of_comm1, date_of_comm2};
    int index_of_post1 = 0;
    add_comment(&storage, index_of_post1, num_comments_post1, comments_post1, date_of_comments);
    char **returned_comments = get_comments(&storage, 0);
    for (int i = 0; i < num_comments_post1; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(returned_comments[i][j], comments_post1[i][j]);
        }
    }
}

TEST(Func, AddingRates) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head_post1[] = "about c++";
    char body_post1[] = "c++ is popular language";
    const char *tags_arr_post1[] = {"c++", "cpp"};
    int creating_day_post1 = 12;
    int creating_month_post1 = 1;
    int creating_year_post1 = 2021;
    int num_tags_post1 = 2;
    create_post(&storage, head_post1, body_post1, num_tags_post1, tags_arr_post1, creating_day_post1, creating_month_post1, creating_year_post1);

    int scores[] = {5, 4, 5};
    add_rate(&storage, 0, 3, scores);
    int *returned_scores = get_scores(&storage, 0);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(returned_scores[i], scores[i]);
    }
}


TEST(Func, PrintMostPost) {
    struct Post_storage storage = {.cur_num_post = 0};
    char head_post1[] = "about c++";
    char body_post1[] = "c++ is popular language";
    const char *tags_arr_post1[] = {"c++", "cpp"};
    int creating_day_post1 = 12;
    int creating_month_post1 = 1;
    int creating_year_post1 = 2021;
    int num_tags_post1 = 2;
    create_post(&storage, head_post1, body_post1, num_tags_post1, tags_arr_post1, creating_day_post1, creating_month_post1, creating_year_post1);

    char head_post2[] = "about python";
    char body_post2[] = "c++ is popular language";
    const char *tags_arr_post2[] = {"python", "numpy"};
    int creating_day_post2 = 23;
    int creating_month_post2 = 1;
    int creating_year_post2 = 2021;
    int num_tags_post2 = 2;
    create_post(&storage, head_post2, body_post2, num_tags_post2, tags_arr_post2, creating_day_post2, creating_month_post2, creating_year_post2);

    const char *comments_post1[] = {"cool++", "nice"};
    int num_comments_post1 = 2;
    struct Date date_of_comm1 = {22, 1, 2021};
    struct Date date_of_comm2 = {7, 2, 2021};
    struct Date date_of_comments[] = {
        date_of_comm1,
        date_of_comm2,
    };
    int index_of_post1 = 0;
    add_comment(&storage, index_of_post1, num_comments_post1, comments_post1, date_of_comments);

    const char *comments_post2[] = {"okey", "and?"};
    int num_comments_post2 = 2;
    struct Date date_of_comm1_post2 = {22, 3, 2021};
    struct Date date_of_comm2_post2 = {24, 1, 2021};
    struct Date date_of_comments_post2[] = {
        date_of_comm1_post2,
        date_of_comm2_post2,
    };
    int index_of_post2 = 0;
    add_comment(&storage, index_of_post2, num_comments_post2, comments_post2, date_of_comments_post2);

    struct Date range_of_dates = {0, 1, 0};
    int result[] = {0};
    int i = 0;
    int *returned_result = find_post_with_high_comm_in_dates(&storage, range_of_dates);
    bool all_arr_printed = false;
    while (!all_arr_printed) {
        if (returned_result[i] == -1) {
            all_arr_printed = true;
        } else {
            EXPECT_EQ(returned_result[i], result[i]);
            i++;
        }
    }
}
