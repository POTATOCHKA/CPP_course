
#include <stdio.h>
#include <stdlib.h>

#define LENGHT_OF_POST_HEAD 50
#define LENGHT_OF_POST_BODY 500
#define NUMBER_OF_TAGS 30
#define TAGS_LENGHT 10
#define NUMBER_OF_COMMENTS 50
#define COMMENT_LENGHT 250
#define NUMBER_OF_SCORES 300
#define CAPACITY_OF_POSTS 50

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
    free(storage->arr_of_posts[index]->comments_arr);
    free(storage->arr_of_posts[index]->dates_of_comment);
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
    free(storage->arr_of_posts[index]->scores_arr);
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

void print_one_post(struct Post_storage *storage, int index) {
    printf("Index of post:%i\n", storage->arr_of_posts[index]->global_index);
    printf("Head of post:%s\n", storage->arr_of_posts[index]->head_of_post);
    printf("Text in post:%s\n", storage->arr_of_posts[index]->body_of_post);
    if (storage->arr_of_posts[index]->num_of_tags > 0) {
        printf("tags:");
        for (int i = 0; i < storage->arr_of_posts[index]->num_of_tags; i++) {
            printf("%s, ", storage->arr_of_posts[index]->tags_arr[i]);
        }
    } else {
        printf("this pos hasnt any tags");
    }
    printf("\n");

    if (storage->arr_of_posts[index]->num_of_comments > 0) {
        for (int i = 0; i < storage->arr_of_posts[index]->num_of_comments; i++) {
            printf("comment:");
            printf("%s\t", storage->arr_of_posts[index]->comments_arr[i]);
            printf("day- %d ", storage->arr_of_posts[index]->dates_of_comment[i][0]);
            printf(" month- %d", storage->arr_of_posts[index]->dates_of_comment[i][1]);
            printf("year- %d\n", storage->arr_of_posts[index]->dates_of_comment[i][2]);
        }
    } else {
        printf("this post hasnt any comments");
    }
    printf("\n");

    if (storage->arr_of_posts[index]->num_of_scores > 0) {
        printf("scores: ");
        for (int i = 0; i < storage->arr_of_posts[index]->num_of_scores; i++) {
            printf("%d, ", storage->arr_of_posts[index]->scores_arr[i]);
        }
    } else {
        printf("this post hasnt any scores");
    }
    printf("\n");
    printf("date of creation - day: %i, month:%i, year:%i", storage->arr_of_posts[index]->date[0],
           storage->arr_of_posts[index]->date[1],
           storage->arr_of_posts[index]->date[2]);
    printf("\n");
}

void read_string_with_limit(char *string, int limit) {
    char c;
    int i = 0;
    for (i; (i < limit - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        string[i] = c;
    }
    if (i == limit - 1) {
        while (1) {
            c = getchar();
            if ((c == EOF) || (c == '\n')) {
                break;
            }
        }
    }

    string[i] = '\0';
}

void print_all_posts(struct Post_storage *storage) {
    printf("\n");
    printf("All posts\n");

    for (int i = 0; i < storage->cur_num_post; i++) {
        print_one_post(storage, i);
        printf("\n");
    }
}
int main() {
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
            (returned_comments[i][j] == comments[i][j]);
        }
    }
    int **returned_dates = get_dates_of_comment(&storage, 0);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            (returned_dates[i][j] == date_of_comments[i][j]);
        }
    }
    return 0;
}
