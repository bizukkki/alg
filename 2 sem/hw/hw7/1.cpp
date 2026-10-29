#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
};

class Tree {
public:
int height() {
    return _height(root);
}

void insert (int key) {
    root = _insert(root, key);
}

private:
Node* root = nullptr;

Node* _insert(Node* tree, int key) {
    if (tree == nullptr){
        Node* node = new Node;
        node->key = key;
        return node;
    }
    if (tree->key > key) {
        tree->left = _insert(tree->left, key);
        return tree;
    } else if (tree->key < key) {
        tree->right = _insert(tree->right, key);
        return tree;
    }
    return tree;
}
int _height(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    int left_height = _height(tree->left);
    int right_height = _height(tree->right);
    return std::max(left_height, right_height) + 1;
}
};

int main() {
    class Tree tree;
    int key;
    std::cin >> key;
    while (key != 0) {
        tree.insert(key);
        std::cin >> key;
    }
    std::cout << tree.height();
}