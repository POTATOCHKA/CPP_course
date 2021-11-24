#pragma once
#include <assert.h>
#include <initializer_list>
#include <iostream>
#include <iterator>

using namespace std;

template <class Key_type, class Compare = std::less<Key_type>>
class Set {
   private:
    struct Node {
        Key_type key;
        unsigned char height;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* next_node = nullptr;
        Node* prev_node = nullptr;
        ~Node() {
            left = NULL;
            delete left;
            right = NULL;
            delete right;
            next_node = NULL;
            delete next_node;
            prev_node = NULL;
            delete prev_node;
        }
    };

    unsigned char height(Node* p);
    void fixheight(Node* p);
    int bfactor(Node* p);
    Node* rotateright(Node* p);
    Node* rotateleft(Node* q);
    Node* balance(Node* p);
    Node* insert_node(Node* p, Key_type k);
    Node* findmin(Node* p);
    Node* removemin(Node* p);
    Node* remove_node(Node* p, Key_type k);
    void delete_set(Node* p);

   public:
    struct Iterator {
        using iterator_category = bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        Key_type operator*() const { return m_ptr->key; }
        pointer operator->() { return m_ptr->key; }
        Iterator& operator++() {
            m_ptr = m_ptr->next_node;
            return *this;
        }
        Iterator& operator--() {
            m_ptr = m_ptr->prev_node;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

       private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(tail); }

    Node* root = nullptr;
    Node* head = nullptr;
    Node* tail = new Node;
    int lenght = 0;

    Set() {}

    Set(initializer_list<Key_type> init_list);
    Set(const Set<Key_type, Compare>& other);
    Set(Set<Key_type, Compare>&& other);

    Set<Key_type, Compare>& operator=(const Set<Key_type, Compare>& other);
    Set<Key_type, Compare>& operator=(Set<Key_type, Compare>&& rhs);

    Node* next(Node* v, Key_type x);
    Node* prev(Node* v, Key_type x);
    Node* search(Node* v, Key_type x);
    void insert(Key_type k);
    void print2DUtil(Node* n, int space);
    void erase(Key_type k);
    int size();
    bool empty();
    Iterator find(Key_type k);
    Node* lower_bound(Key_type x);
    ~Set() {
    }
};

#include "Set_definition.hpp"