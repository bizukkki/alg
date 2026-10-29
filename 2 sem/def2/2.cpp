#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
};

class Tree {
public:
int height() {
    return _height(root);
}

void insert (int key) {
    root = _insert(root, key, nullptr);
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
int parent(int key) {
    return _parent(root, key);
}

private:
Node* root = nullptr;

Node* _insert(Node* tree, int key, Node* parent) {
    if (tree == nullptr){
        Node* node = new Node;
        node->key = key;
        node->parent = parent;
        return node;
    }
    if (tree->key > key) {
        tree->left = _insert(tree->left, key, tree);
        tree->parent = parent;
        return tree;
    } else if (tree->key < key) {
        tree->right = _insert(tree->right, key, tree);
        tree->parent = parent;
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
int _parent(Node* tree, int key) {
    if (tree->key == key) {
        if (tree->parent != nullptr){
            return tree->parent->key;
        } else return -1;
    }
    if (tree->key > key) {
        return _parent(tree->left, key);
    } else if (tree->key < key) {
        return _parent(tree->right, key);
    }
    if (tree->parent != nullptr){
            return tree->parent->key;
        } else return -1;
}
};

int main() {
    class Tree tree;
    int n;
    std::cin >> n;
    int type, x;
    std::vector<int> answer;
    for (int i = 0; i < n; i++){
        std::cin >> type >> x;
        if (type == 1) {
            tree.insert(x);
        } else {
            answer.push_back(tree.parent(x));
        }
    }
    for (auto a : answer) {
        std::cout << a << "\n";
    }
}