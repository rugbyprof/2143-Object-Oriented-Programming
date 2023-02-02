#include <iostream>

struct Node {
  int data;
  Node *left;
  Node *right;
};

class BST {
private:
  Node *root;

  Node *insert(Node *node, int data) {
    if (node == NULL) {
      node = new Node();
      node->data = data;
      node->left = NULL;
      node->right = NULL;
    } else if (data <= node->data) {
      node->left = insert(node->left, data);
    } else {
      node->right = insert(node->right, data);
    }
    return node;
  }

  void print(Node *node) {
    if (node == NULL)
      return;
    print(node->left);
    std::cout << node->data << " ";
    print(node->right);
  }

public:
  BST() { root = NULL; }

  void insert(int data) { root = insert(root, data); }

  void print() { print(root); }
};

int main() {
  BST tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(17);
  tree.print();
  return 0;
}
