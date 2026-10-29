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

int findMax() {
    if (root == nullptr) {
        return 0;
    }
    Node* runner = root;
    while (runner->right != nullptr){
        runner = runner->right;
    }
    return runner->key;

}
void removeMax() {
    root = _removeMax(root);
}

void inorder(std::vector<int>& result) {
    _inorder(root, result);
}
void leafs(std::vector<int>& result) {
    _leafs(root, result);
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

Node* _removeMax(Node* tree){
    if (tree == nullptr) {
        return nullptr;
    }
    if (tree->right == nullptr) {
        Node* gc = tree->left;
        delete tree;
        return gc;
    }
    tree->right = _removeMax(tree->right);
    return tree;
}

void _inorder(Node* tree, std::vector<int>& result) {
    if (tree == nullptr) {
        return;
    }
    _inorder(tree->left, result);
    result.push_back(tree->key);
    _inorder(tree->right, result);
}
void _leafs(Node* tree, std::vector<int>& result) {
    if (tree == nullptr) {
        return;
    }
    _leafs(tree->left, result);
    if ((tree->left == nullptr && tree->right != nullptr)
        || (tree->left != nullptr && tree->right == nullptr)) {
        result.push_back(tree->key);
    } 
    _leafs(tree->right, result);
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
    std::vector<int> result;
    tree.leafs(result);
    for (auto a : result) {
        std::cout << a << "\n";
    }
}