
#include "Post_creator.h"

//не понял вашего комменатрия о том, что нужно возвращать созданный пост. Ведь
// мы делаем блог, а там при создании поста просто должна обновляться лента.
// Поэтому не стал менять функцию

void create_post(struct Post_storage *storage, char *head_post, char *body_post,
                 int num_tags, const char **tags_arr, int day, int month, int year) {
    struct Date date_of_post = {day, month, year};
    struct Post new_post = {
        .global_index = storage->cur_num_post,
        .head_of_post = head_post,
        .body_of_post = body_post,
        .num_of_tags = num_tags,
        .tags_arr = tags_arr,
        .date_of_post = date_of_post,
        .num_of_comments = 0,
        .num_of_scores = 0,
    };
    storage->arr_of_posts[storage->cur_num_post] = new_post;
    storage->cur_num_post++;
}

char *get_head_of_post(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].head_of_post;
}
char *get_body_of_post(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].body_of_post;
}
int get_num_of_tags(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].num_of_tags;
}
char **get_tags_arr(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].tags_arr;
}
struct Date get_date(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].date_of_post;
}
char **get_comments(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].comments_arr;
}
struct Date *get_dates_of_comment(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].dates_of_comment;
}
int *get_scores(struct Post_storage *storage, int index) {
    return storage->arr_of_posts[index].scores_arr;
}

void add_comment(struct Post_storage *storage, int index, size_t num_comments,
                 const char **coments_arr, struct Date *comments_date) {
    char **dynamic_comments_arr = malloc(NUMBER_OF_TAGS * sizeof(char *));
    assert(dynamic_comments_arr != NULL);

    for (int i = 0; i < NUMBER_OF_TAGS; ++i) {
        dynamic_comments_arr[i] = malloc(TAGS_LENGHT * sizeof(char));
        assert(dynamic_comments_arr[i] != NULL);
    }
    struct Date *dynamic_comments_date = malloc(NUMBER_OF_TAGS * sizeof(struct Date *));
    assert(dynamic_comments_date != NULL);

    for (size_t i = 0; i < storage->arr_of_posts[index].num_of_comments; i++) {
        dynamic_comments_arr[i] = storage->arr_of_posts[index].comments_arr[i];
        dynamic_comments_date[i] = storage->arr_of_posts[index].dates_of_comment[i];
    }
    free(storage->arr_of_posts[index].comments_arr);
    free(storage->arr_of_posts[index].dates_of_comment);
    for (size_t i = 0; i < num_comments; i++) {
        dynamic_comments_arr[i + storage->arr_of_posts[index].num_of_comments] = coments_arr[i];
        dynamic_comments_date[i + storage->arr_of_posts[index].num_of_comments] = comments_date[i];
    }
    storage->arr_of_posts[index].comments_arr = dynamic_comments_arr;
    storage->arr_of_posts[index].dates_of_comment = dynamic_comments_date;
    storage->arr_of_posts[index].num_of_comments += num_comments;
}

void add_rate(struct Post_storage *storage, int index, int num_rates,
              int *rates) {
    int *dynamaic_rates = malloc(NUMBER_OF_SCORES * sizeof(int));
    assert(dynamaic_rates != NULL);

    for (int i = 0; i < storage->arr_of_posts[index].num_of_scores; i++) {
        dynamaic_rates[i] = storage->arr_of_posts[index].scores_arr[i];
    }
    free(storage->arr_of_posts[index].scores_arr);
    for (int i = 0; i < num_rates; i++) {
        dynamaic_rates[i + storage->arr_of_posts[index].num_of_scores] = rates[i];
    }
    storage->arr_of_posts[index].scores_arr = dynamaic_rates;
    storage->arr_of_posts[index].num_of_scores += num_rates;
}

int calculate_date_in_days(struct Date cur_date) {
    int num_days = cur_date.day + cur_date.month * 30 + cur_date.year * 365;
    return num_days;
}

int *find_post_with_high_comm_in_dates(struct Post_storage *storage, struct Date range_time) {
    /*
        эта функция ищет все посты с наибольшим количеством комментариев, за время range_time
        от создания поста

    */
    int date_posting_post_in_days;
    int date_posting_comm_in_Days;
    int range_time_in_days = calculate_date_in_days(range_time);
    int max_coms = -1;
    int temp_num_coms;
    for (int index = 0; index < storage->cur_num_post; index++) {
        temp_num_coms = 0;
        date_posting_post_in_days = calculate_date_in_days(storage->arr_of_posts[index].date_of_post);
        for (size_t j = 0; j < storage->arr_of_posts[index].num_of_comments; j++) {
            date_posting_comm_in_Days = calculate_date_in_days(storage->arr_of_posts[index].dates_of_comment[j]);
            if ((date_posting_comm_in_Days - date_posting_post_in_days > 0) && (date_posting_comm_in_Days - date_posting_post_in_days < range_time_in_days)) {
                temp_num_coms++;
            }
        }
        if (temp_num_coms > max_coms) {
            max_coms = temp_num_coms;
        }
    }
    int *answer = malloc(CAPACITY_OF_POSTS * sizeof(int));
    assert(answer != NULL);
    int index_in_arr_with_max_coms = 0;
    for (int index = 0; index < storage->cur_num_post; index++) {
        temp_num_coms = 0;
        date_posting_post_in_days = calculate_date_in_days(storage->arr_of_posts[index].date_of_post);
        for (size_t j = 0; j < storage->arr_of_posts[index].num_of_comments; j++) {
            date_posting_comm_in_Days = calculate_date_in_days(storage->arr_of_posts[index].dates_of_comment[j]);
            if ((date_posting_comm_in_Days - date_posting_post_in_days > 0) && (date_posting_comm_in_Days - date_posting_post_in_days < range_time_in_days)) {
                temp_num_coms++;
            }
        }
        if (temp_num_coms == max_coms) {
            answer[index_in_arr_with_max_coms] = index;
            index_in_arr_with_max_coms++;
        }
    }

    answer[index_in_arr_with_max_coms] = -1;
    /*
        выглядит как копипаста. Но здесь мы сначала находим максимальное количество комментариев
        подходящих по дате, а потом их добавляем. Способа элегантнее я не придумал.
        -1 в строчке выше это флаг, который говорит, что индексация постов наивысшим количеством комментов
        закончена. То есть таким образом я ловлю случай когда есть несколько постов с одинаковым количеством
        комментов.
    */
    return answer;
}