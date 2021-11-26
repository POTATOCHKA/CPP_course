#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LENGHT_OF_POST_HEAD 50
#define LENGHT_OF_POST_BODY 500
#define NUMBER_OF_TAGS 30
#define TAGS_LENGHT 10
#define NUMBER_OF_COMMENTS 50
#define COMMENT_LENGHT 250
#define NUMBER_OF_SCORES 300
#define CAPACITY_OF_POSTS 50

struct Date {
    int day;
    int month;
    int year;
};

struct Post {
    int global_index;
    char *head_of_post;
    char *body_of_post;
    int num_of_tags;
    char **tags_arr;
    size_t num_of_comments;
    char **comments_arr;
    struct Date *dates_of_comment;
    int num_of_scores;
    int *scores_arr;
    struct Date date_of_post;
};

struct Post_storage {
    int cur_num_post;
    struct Post arr_of_posts[CAPACITY_OF_POSTS];
};

char *get_head_of_post(struct Post_storage *storage, int index);
char *get_body_of_post(struct Post_storage *storage, int index);
int get_num_of_tags(struct Post_storage *storage, int index);
char **get_tags_arr(struct Post_storage *storage, int index);
struct Date get_date(struct Post_storage *storage, int index);
char **get_comments(struct Post_storage *storage, int index);
struct Date *get_dates_of_comment(struct Post_storage *storage, int index);
int *get_scores(struct Post_storage *storage, int index);
void read_string_with_limit(char *string, int limit);
void create_post(struct Post_storage *storage, char *head_post, char *body_post,
                 int num_tags, const char **tags_arr, int day, int month, int year);
void add_comment(struct Post_storage *storage, int index, size_t num_comments,
                 const char **coments_arr, struct Date *comments_date);
void add_rate(struct Post_storage *storage, int index, int num_rates, int *rates);
int *find_post_with_high_comm_in_dates(struct Post_storage *storage, struct Date range_time);