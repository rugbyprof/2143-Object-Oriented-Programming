#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node *left;
    Node *right;
    Node();
    Node(T);
};

template <typename T>
class Bst {
private:
    Node<T> *root;
    int size;
    void Print(Node<T> *);
    void Insert(Node<T> *&, T);
    bool Find(Node<T> *, T);
    void BuildGraphViz(Node<T> *);

public:
    Bst();
    Bst(T *);
    void Insert(T);
    void Print();
    bool Find(T);
    void Delete();
    void BuildGraphViz();
    void PrintGraphViz();
};

template <typename T>
Node<T>::Node() {
    data = 0;
    left = right = NULL;
}

template <typename T>
Node<T>::Node(T x) {
    data = x;
    left = right = NULL;
}

template <typename T>
Bst<T>::Bst() {
    size = 0;
    root = NULL;
}

// Bst<T>::Bst(T *A) {
// }

template <typename T>
void Bst<T>::Insert(Node<T> *&root, T val) {
    if (!root) {
        root = new Node<T>(val);
        return;
    } else {
        if (root->data > val) {
            Insert(root->left, val);
        } else {
            Insert(root->right, val);
        }
    }
}

template <typename T>
void Bst<T>::Insert(T data) {
    if (!root) {
        Node<T> *temp = new Node<T>(data);
        root = temp;
    } else {
        Insert(root, data);
    }
}

template <typename T>
void Bst<T>::Print() {
    Print(root);
}

template <typename T>
void Bst<T>::Print(Node<T> *root) {
    if (!root) {
        return;
    } else {
        //PreOrder
        Print(root->left);
        cout << root->data << " ";
        //InOrder
        Print(root->right);
        //PostOrder
    }
}

template <typename T>
bool Bst<T>::Find(Node<T> *root, T key) {
    if (!root) {
        return false;
    } else {
        //PreOrder
        if (root->data == key) {
            return true;
        } else if (key < root->data) {
            return Find(root->left, key);
        } else {
            return Find(root->right, key);
        }
    }
}

template <typename T>
bool Bst<T>::Find(T key) {
    return Find(root, key);
}

template <typename T>
void Bst<T>::Delete() {
}