#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    int count;
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

void inorder(std::vector<std::pair<int, int>>& result) {
    _inorder(root, result);
}


private:
Node* root = nullptr;

Node* _insert(Node* tree, int key) {
    if (tree == nullptr){
        Node* node = new Node;
        node->key = key;
        node->count = 1;
        return node;
    }
    if (tree->key > key) {
        tree->left = _insert(tree->left, key);
        return tree;
    } else if (tree->key < key) {
        tree->right = _insert(tree->right, key);
        return tree;
    } else {
        tree->count+=1;
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

void _inorder(Node* tree, std::vector<std::pair<int, int>>& result) {
    if (tree == nullptr) {
        return;
    }
    _inorder(tree->left, result);
    result.push_back({tree->key, tree->count});
    _inorder(tree->right, result);
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
    std::vector<std::pair<int, int>> result;
    tree.inorder(result);
    for (auto i : result) {
        std::cout << i.first << " " << i.second << "\n";
    }
}