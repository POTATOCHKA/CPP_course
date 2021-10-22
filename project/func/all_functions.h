#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

struct Post {
    int global_index;
    char *head_of_post;
    char *body_of_post;
    int num_of_tags;
    char **tags_arr;
    int num_of_comments;
    char **comments_arr;
    int **dates_of_comment;
    int num_of_scores;
    int *scores_arr;
    int *date;
};

struct Post_storage {
    int cur_num_post;
    struct Post *arr_of_posts[CAPACITY_OF_POSTS];
};

int *print_kek();

char *get_head_of_post(struct Post_storage *storage, int index);
char *get_body_of_post(struct Post_storage *storage, int index);
int get_num_of_tags(struct Post_storage *storage, int index);
char **get_tags_arr(struct Post_storage *storage, int index);
int *get_date(struct Post_storage *storage, int index);
char **get_comments(struct Post_storage *storage, int index);
int **get_dates_of_comment(struct Post_storage *storage, int index);
int *get_scores(struct Post_storage *storage, int index);
void read_string_with_limit(char *string, int limit);
void create_post(struct Post_storage *storage, char *head_post, char *body_post,
                 int num_tags, char **tags_arr, int day, int month, int year);
void add_comment(struct Post_storage *storage, int index,
                 int num_comments, char **coments_arr, int **comments_date);
void add_rate(struct Post_storage *storage, int index, int num_rates, int *rates);
int *find_post_with_high_comm(struct Post_storage *storage);
