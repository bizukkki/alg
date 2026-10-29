#include <iostream>
#include <vector>

struct Node {
    int key;
    int left = 0;
    int right = 0;
    char color;
};

class Tree {
private:
    std::vector<Node> nodes;
    int root;
    bool flag = true;

    void _insert(int id, int key, int left, int right, char color) {
        nodes[id].key = key;
        nodes[id].left = left;
        nodes[id].right = right;
        nodes[id].color = color;
    }
    bool _check_keys(Node* tree) {
        if (tree == nullptr) {
            return flag;
        }
        if (!flag) return false;
        if (tree->left) {
            if (nodes[tree->left].key > tree->key) flag = false;
        }
        if (tree->right) {
            if (nodes[tree->right].key < tree->key) flag = false;
        }
        _check_keys(nodes[tree->left]);
        _check_keys(nodes[tree->right]);
        return flag;

    }

public:
    Tree(int n) {
        nodes.resize(n + 1);
    }
    void setRoot(int r) {
        root = r;
    }
    void insert(int id, int key, int left, int right, char color) {
        _insert(id, key, left, right, color);
    }
    bool isRBTree() {
        if (nodes[root].color != 'B') {
            return false;
        }
        if (!_check_keys(root) {
            return false;
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    if (n == 0) {
        return 0;
    }
    int root;
    std::cin >> root;
    Tree tree(n);
    tree.setRoot(root);

    for (int i = 0; i < n; ++i) {
        int number;
        int key;
        std::string left;
        std::string right;
        char color;

        std::cin >> number >> key >> left >> right >> color;

        int left_num = 0;
        int right_num = 0;

        if (left != "null") {
            left_num = std::stoi(left);
        }

        if (right != "null") {
            right_num = std::stoi(right);
        }

        tree.insert(number, key, left_num, right_num, color);
    }
}