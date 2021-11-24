
#pragma once
#include "Set.h"

template <class Key_type, class Compare>
Set<Key_type, Compare>::Set(initializer_list<Key_type> init_list) {
    for (auto it = init_list.begin(); it != init_list.end(); ++it) {
        insert(*it);
    }
}

template <class Key_type, class Compare>
Set<Key_type, Compare>::Set(const Set<Key_type, Compare>& other) {
    Node* t = other.head;
    while (t != other.tail) {
        insert(t->key);
        t = t->next_node;
    }
}

template <class Key_type, class Compare>
Set<Key_type, Compare>::Set(Set<Key_type, Compare>&& other) {
    root = other.root;
    head = other.head;
    tail = other.tail;
    lenght = other.lenght;
    other.root = nullptr;
    other.head = nullptr;
    other.tail = nullptr;
}
template <class Key_type, class Compare>
Set<Key_type, Compare>& Set<Key_type, Compare>::operator=(const Set<Key_type, Compare>& other) {
    if (this == &other) {
        return *this;
    }
    Node* t = other.head;
    while (t != other.tail) {
        insert(t->key);
        t = t->next_node;
    }
    return *this;
}

template <class Key_type, class Compare>
Set<Key_type, Compare>& Set<Key_type, Compare>::operator=(Set<Key_type, Compare>&& rhs) {
    root = rhs.root;
    head = rhs.head;
    tail = rhs.tail;
    lenght = rhs.lenght;
    return *this;
}

template <class Key_type, class Compare>
unsigned char Set<Key_type, Compare>::height(Node* p) {
    if (p == nullptr) {
        return 0;
    }
    return p->height;
}

template <class Key_type, class Compare>
int Set<Key_type, Compare>::bfactor(Node* p) {
    return height(p->right) - height(p->left);
}

template <class Key_type, class Compare>
void Set<Key_type, Compare>::fixheight(Node* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    if (hl > hr) {
        p->height = hl + 1;
    } else {
        p->height = hr + 1;
    }
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::rotateright(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::rotateleft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::balance(Node* p) {
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::insert_node(Node* p, Key_type k) {
    if (p == nullptr) {
        lenght++;
        Node* temp = new Node;
        temp->key = k;
        return temp;
    }
    if (p->key == k) {
        return p;
    } else {
        if (k < p->key)
            p->left = insert_node(p->left, k);
        else
            p->right = insert_node(p->right, k);
        return balance(p);
    }
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::next(Node* v, Key_type x) {
    Node* res = tail;
    while (v != nullptr) {
        if (v->key > x) {
            res = v;
            v = v->left;
        } else {
            v = v->right;
        }
    }
    return res;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::search(Node* v, Key_type x) {
    if (v == nullptr) {
        return nullptr;
    } else if (x < v->key) {
        return search(v->left, x);
    } else if (x > v->key) {
        return search(v->right, x);
    }
    return v;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::prev(Node* v, Key_type x) {
    Node* res = nullptr;
    while (v != nullptr) {
        if (v->key < x) {
            res = v;
            v = v->right;
        } else {
            v = v->left;
        }
    }
    return res;
}

template <class Key_type, class Compare>
void Set<Key_type, Compare>::insert(Key_type key) {
    root = insert_node(root, key);
    Node* inserted_node = search(root, key);
    Node* previous_node = prev(root, key);
    Node* next_node = next(root, key);
    if (previous_node == nullptr) {
        head = inserted_node;
    } else {
        previous_node->next_node = inserted_node;
    }
    inserted_node->prev_node = previous_node;
    inserted_node->next_node = next_node;
    if ((next_node == tail)) {
        tail->prev_node = inserted_node;
    } else {
        next_node->prev_node = inserted_node;
    }
}

template <class Key_type, class Compare>
void Set<Key_type, Compare>::print2DUtil(Node* n, int space) {
    if (n == nullptr)
        return;
    space += 4;
    print2DUtil(n->right, space);
    cout << endl;
    for (int i = 4; i < space; i++)
        cout << " ";
    cout << n->key << "\n";
    print2DUtil(n->left, space);
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::findmin(Node* p) {
    if (p->left != nullptr) {
        return findmin(p->left);
    }
    return p;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::removemin(Node* p) {
    if (p->left == nullptr)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::remove_node(Node* p, Key_type k) {
    if (p == nullptr) {
        return nullptr;
    }
    if (k < p->key)
        p->left = remove_node(p->left, k);
    else if (k > p->key)
        p->right = remove_node(p->right, k);
    else {
        lenght--;
        Node* q = p->left;
        Node* r = p->right;
        if (p->prev_node != nullptr) {
            p->prev_node->next_node = p->next_node;
        } else {
            head = p->next_node;
        }
        if (p->next_node != tail) {
            p->next_node->prev_node = p->prev_node;
        } else {
            tail->prev_node = p->prev_node;
        }

        delete p;
        if (r == nullptr) {
            return q;
        }
        Node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

template <class Key_type, class Compare>
void Set<Key_type, Compare>::erase(Key_type k) {
    root = remove_node(root, k);
}

template <class Key_type, class Compare>
void Set<Key_type, Compare>::delete_set(Node* p) {
    if (p == nullptr) {
        return;
    }
    delete_set(p->left);
    delete_set(p->right);
    delete p;
}

template <class Key_type, class Compare>
int Set<Key_type, Compare>::size() {
    return lenght;
}

template <class Key_type, class Compare>
bool Set<Key_type, Compare>::empty() {
    if (lenght == 0) {
        return true;
    }
    return false;
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Iterator Set<Key_type, Compare>::find(Key_type k) {
    Node* tmp = search(root, k);
    if (tmp == nullptr) {
        return end();
    } else {
        Iterator it = tmp;
        return it;
    }
}

template <class Key_type, class Compare>
typename Set<Key_type, Compare>::Node* Set<Key_type, Compare>::lower_bound(Key_type x) {
    Node* v = root;
    Node* res = tail;
    while (v != nullptr) {
        if (v->key > x) {
            res = v;
            v = v->left;
        } else if (v->key == x) {
            res = v;
            return res;
        } else {
            v = v->right;
        }
    }
    return res;
}