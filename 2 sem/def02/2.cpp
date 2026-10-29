#include <iostream>
#include <vector>
#include <queue>

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
    std::queue<Node*> q;
    if (tree == nullptr) {
        return;
    }
    q.push(tree);
    while (!q.empty()) {
        Node* now = q.front();
        q.pop();
        result.push_back(now->key);
        if (now->left != nullptr) {
            q.push(now->left);
        }
        if (now->right != nullptr) {
            q.push(now->right);
        }
    }
}
};

int main() {
    class Tree tree;
    int n;
    std::cin >> n;
    int key;
    for(int i = 0; i < n; i++) {
        std::cin >> key;
        tree.insert(key);
    }
    std::vector<int> result;
    tree.inorder(result);
    for (auto a : result) {
        std::cout << a << " ";
    }
}


//10
//74 32 44 18 65 90 82 43 81 17

//74 32 90 18 44 82 17 43 65 81 - nedd
//74 32 90 18 44 82 17 43 65 81

//74 32 18 17 44 43 65 90 82 81 -have 