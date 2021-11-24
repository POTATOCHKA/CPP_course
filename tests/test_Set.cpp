#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <set>
#include <vector>

#include "Set.h"

TEST(Func, check_constness) {
    Set<int> s({7, 3, 1, 2, 4, 6, 12, 9, 5, 20, 11, 12, 4, 6});
    int tmp = *s.find(4);
    EXPECT_EQ(tmp, 4);
    EXPECT_EQ(s.lower_bound(12)->key, 12);
    EXPECT_EQ(s.lower_bound(14)->key, 20);
    EXPECT_EQ(s.lower_bound(30), s.end());
    EXPECT_EQ(s.empty(), false);
    Set<int> s1({1, 1, 1, 1, 1});
    EXPECT_EQ(s1.size(), 1);
    auto first_el = s.begin();
    EXPECT_EQ(*first_el, 1);
}

TEST(Func, check_copy_correctness) {
    Set<int> s = {1, 2, 3};
    Set<int> s1;
    s1 = s;
    s.insert(4);
    s.insert(5);
    Set<int> test_set = {1, 2, 3};
    auto it1 = s1.begin();
    auto it2 = test_set.begin();
    for (int t = 0; it1 != s1.end() && it2 != test_set.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }

    Set<int> s2 = s;
    int i = 1;
    for (auto it : s2) {
        EXPECT_EQ(it, i);
        i++;
    }
}

TEST(Func, check_iterators) {
    Set<int> s = {4, 5, 3, 2, 1};
    int num = 1;
    for (auto it = s.begin(); it != s.end(); ++it) {
        EXPECT_EQ(*it, num);
        num++;
    }

    auto last = s.end();
    last--;
    last--;
    EXPECT_EQ(*last, 4);
}

TEST(Func, check_insert_erase) {
    Set<int> s;
    EXPECT_EQ(s.empty(), true);
    s.insert(3);
    s.insert(2);
    s.insert(4);
    s.insert(1);
    s.insert(5);
    s.insert(6);
    s.insert(7);

    s.erase(4);
    s.erase(5);

    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.find(5), s.end());
    EXPECT_EQ(*s.find(7), 7);

    EXPECT_EQ(s.lower_bound(4)->key, 6);
    EXPECT_EQ(s.lower_bound(2)->key, 2);
    EXPECT_EQ(s.lower_bound(8), s.end());
}

TEST(Func, check_time_of_work) {
    set<int> std_set;
    Set<int> my_set;
    vector<int> values(10000);
    auto f = []() -> int { return rand() % 10000; };
    generate(values.begin(), values.end(), f);
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        std_set.insert(values[i]);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration_of_insert_std_set = chrono::duration_cast<chrono::milliseconds>(stop - start);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        my_set.insert(values[i]);
    }
    stop = chrono::high_resolution_clock::now();

    auto duration_of_insert_my_set = chrono::duration_cast<chrono::milliseconds>(stop - start);
    EXPECT_LE(duration_of_insert_my_set, duration_of_insert_std_set * 10);

    int temp;
    start = chrono::high_resolution_clock::now();
    for (auto it : std_set) {
        temp = it;
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_iteration_std = chrono::duration_cast<chrono::microseconds>(stop - start);

    start = chrono::high_resolution_clock::now();
    for (auto it : my_set) {
        temp = it;
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_iteration_my_set = chrono::duration_cast<chrono::microseconds>(stop - start);

    EXPECT_LE(duration_of_iteration_my_set, duration_of_iteration_std * 10);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        std_set.find(values[i]);
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_find_std_set = chrono::duration_cast<chrono::microseconds>(stop - start);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        my_set.find(values[i]);
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_find_my_set = chrono::duration_cast<chrono::microseconds>(stop - start);

    EXPECT_LE(duration_of_find_my_set, duration_of_find_std_set * 10);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        std_set.erase(values[i]);
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_erase_std_set = chrono::duration_cast<chrono::microseconds>(stop - start);

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < values.size(); i++) {
        my_set.erase(values[i]);
    }
    stop = chrono::high_resolution_clock::now();
    auto duration_of_erase_my_set = chrono::duration_cast<chrono::microseconds>(stop - start);

    EXPECT_LE(duration_of_erase_my_set, duration_of_erase_std_set * 10);
}
