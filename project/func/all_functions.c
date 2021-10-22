
#include "all_functions.h"

void create_post(struct Post_storage *storage, char *head_post, char *body_post,
                 int num_tags, char **tags_arr, int day, int month, int year) {
    struct Post *new_post;
    new_post = malloc(sizeof(struct Post));
    new_post->global_index = storage->cur_num_post;
    new_post->head_of_post = head_post;
    new_post->body_of_post = body_post;
    new_post->num_of_tags = num_tags;
    new_post->tags_arr = tags_arr;
    int *date = malloc(3 * sizeof(int));
    date[0] = day;
    date[1] = month;
    date[2] = year;
    new_post->date = date;
    new_post->num_of_comments = 0;
    new_post->num_of_scores = 0;
    storage->arr_of_posts[storage->cur_num_post] = new_post;
    storage->cur_num_post++;
}

char *get_head_of_post(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->head_of_post;
}
char *get_body_of_post(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->body_of_post;
}
int get_num_of_tags(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->num_of_tags;
}
char **get_tags_arr(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->tags_arr;
}
int *get_date(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->date;
}
char **get_comments(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->comments_arr;
}
int **get_dates_of_comment(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->dates_of_comment;
}
int *get_scores(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index]->scores_arr;
}

void add_comment(struct Post_storage *storage, int index, int num_comments,
                 char **coments_arr, int **comments_date) {
    char **dynamic_comments_arr = malloc(NUMBER_OF_TAGS * sizeof(char *));
    for (int i = 0; i < NUMBER_OF_TAGS; ++i) {
        dynamic_comments_arr[i] = malloc(TAGS_LENGHT * sizeof(char));
    }
    int **dynamic_comments_date = malloc(NUMBER_OF_TAGS * sizeof(int *));
    for (int i = 0; i < NUMBER_OF_TAGS; ++i) {
        dynamic_comments_date[i] = malloc(TAGS_LENGHT * sizeof(int));
    }
    for (int i = 0; i < storage->arr_of_posts[index]->num_of_comments; i++) {
        dynamic_comments_arr[i] = storage->arr_of_posts[index]->comments_arr[i];
        dynamic_comments_date[i] = storage->arr_of_posts[index]->dates_of_comment[i];
    }
    for (int i = 0; i < num_comments; i++) {
        dynamic_comments_arr[i + storage->arr_of_posts[index]->num_of_comments] = coments_arr[i];
        dynamic_comments_date[i + storage->arr_of_posts[index]->num_of_comments] = comments_date[i];
    }
    storage->arr_of_posts[index]->comments_arr = dynamic_comments_arr;
    storage->arr_of_posts[index]->dates_of_comment = dynamic_comments_date;
    storage->arr_of_posts[index]->num_of_comments += num_comments;
}

void add_rate(struct Post_storage *storage, int index, int num_rates,
              int *rates) {
    int *dynamaic_rates = malloc(NUMBER_OF_SCORES * sizeof(int));
    for (int i = 0; i < storage->arr_of_posts[index]->num_of_scores; i++) {
        dynamaic_rates[i] = storage->arr_of_posts[index]->scores_arr[i];
    }
    for (int i = 0; i < num_rates; i++) {
        dynamaic_rates[i + storage->arr_of_posts[index]->num_of_scores] = rates[i];
    }
    storage->arr_of_posts[index]->scores_arr = dynamaic_rates;
    storage->arr_of_posts[index]->num_of_scores += num_rates;
}

int *find_post_with_high_comm(struct Post_storage *storage) {
    int max_coms = -1;
    int temp_coms;
    int date1;
    int date2;
    for (int i = 0; i < storage->cur_num_post; i++) {
        temp_coms = 0;
        int post_day = storage->arr_of_posts[i]->date[0];
        int post_month = storage->arr_of_posts[i]->date[1];
        int post_year = storage->arr_of_posts[i]->date[2];
        date1 = post_day + post_month * 30 + post_year * 365;
        for (int j = 0; j < storage->arr_of_posts[i]->num_of_comments; j++) {
            int comment_day = storage->arr_of_posts[i]->dates_of_comment[j][0];
            int comment_month = storage->arr_of_posts[i]->dates_of_comment[j][1];
            int comment_year = storage->arr_of_posts[i]->dates_of_comment[j][2];
            date2 = comment_day + comment_month * 30 + comment_year * 365;
            if ((date2 - date1 > 0) && (date2 - date1 < 31)) {
                temp_coms++;
            }
        }
        if (temp_coms > max_coms) {
            max_coms = temp_coms;
        }
    }
    int *answer = malloc(CAPACITY_OF_POSTS * sizeof(int));
    int k = 0;
    for (int i = 0; i < storage->cur_num_post; i++) {
        temp_coms = 0;
        int post_day = storage->arr_of_posts[i]->date[0];
        int post_month = storage->arr_of_posts[i]->date[1];
        int post_year = storage->arr_of_posts[i]->date[2];
        date1 = post_day + post_month * 30 + post_year * 365;
        for (int j = 0; j < storage->arr_of_posts[i]->num_of_comments; j++) {
            int comment_day = storage->arr_of_posts[i]->dates_of_comment[j][0];
            int comment_month = storage->arr_of_posts[i]->dates_of_comment[j][1];
            int comment_year = storage->arr_of_posts[i]->dates_of_comment[j][2];
            date2 = comment_day + comment_month * 30 + comment_year * 365;
            if ((date2 - date1 > 0) && (date2 - date1 < 31)) {
                temp_coms++;
            }
        }
        if (temp_coms == max_coms) {
            answer[k] = i;
            k++;
        }
    }
    answer[k] = -100;
    return answer;
}
