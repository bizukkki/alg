#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Node {
    int key = 0;
    int left = 0;
    int right = 0;
    char color = 'B';
};

struct CheckItem {
    int v;
    long long min_key;
    long long max_key;
};

struct OrderItem {
    int v;
    bool used;
};

class Tree {
private:
    std::vector<Node> nodes;
    int root = 0;

    void _insert(int id, int key, int left, int right, char color) {
        nodes[id].key = key;
        nodes[id].left = left;
        nodes[id].right = right;
        nodes[id].color = color;
    }

    bool _check_keys() {
        std::vector<CheckItem> stack;

        CheckItem first;
        first.v = root;
        first.min_key = std::numeric_limits<long long>::min();
        first.max_key = std::numeric_limits<long long>::max();

        stack.push_back(first);

        while (!stack.empty()) {
            CheckItem now = stack.back();
            stack.pop_back();

            if (now.v == 0) {
                continue;
            }

            long long key = nodes[now.v].key;

            if (!(now.min_key < key && key < now.max_key)) {
                return false;
            }

            CheckItem left_item;
            left_item.v = nodes[now.v].left;
            left_item.min_key = now.min_key;
            left_item.max_key = key;
            stack.push_back(left_item);

            CheckItem right_item;
            right_item.v = nodes[now.v].right;
            right_item.min_key = key;
            right_item.max_key = now.max_key;
            stack.push_back(right_item);
        }

        return true;
    }

    bool _check_colors_and_red_rule() {
        std::vector<int> stack;
        stack.push_back(root);

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();

            if (v == 0) {
                continue;
            }

            if (nodes[v].color != 'R' && nodes[v].color != 'B') {
                return false;
            }

            if (nodes[v].color == 'R') {
                int left = nodes[v].left;
                int right = nodes[v].right;

                if (left != 0 && nodes[left].color == 'R') {
                    return false;
                }

                if (right != 0 && nodes[right].color == 'R') {
                    return false;
                }
            }

            stack.push_back(nodes[v].left);
            stack.push_back(nodes[v].right);
        }

        return true;
    }

    bool _check_black_height() {
        std::vector<int> black_height(nodes.size(), 0);
        std::vector<OrderItem> stack;

        OrderItem first;
        first.v = root;
        first.used = false;
        stack.push_back(first);

        while (!stack.empty()) {
            OrderItem now = stack.back();
            stack.pop_back();

            if (now.v == 0) {
                continue;
            }

            if (!now.used) {
                OrderItem current;
                current.v = now.v;
                current.used = true;
                stack.push_back(current);

                OrderItem right_item;
                right_item.v = nodes[now.v].right;
                right_item.used = false;
                stack.push_back(right_item);

                OrderItem left_item;
                left_item.v = nodes[now.v].left;
                left_item.used = false;
                stack.push_back(left_item);
            } else {
                int left = nodes[now.v].left;
                int right = nodes[now.v].right;

                int left_height;
                int right_height;

                if (left == 0) {
                    left_height = 1;
                } else {
                    left_height = black_height[left];
                }

                if (right == 0) {
                    right_height = 1;
                } else {
                    right_height = black_height[right];
                }

                if (left_height != right_height) {
                    return false;
                }

                black_height[now.v] = left_height;

                if (nodes[now.v].color == 'B') {
                    black_height[now.v]++;
                }
            }
        }

        return true;
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
        if (root == 0) {
            return true;
        }

        if (nodes[root].color != 'B') {
            return false;
        }

        if (!_check_keys()) {
            return false;
        }

        if (!_check_colors_and_red_rule()) {
            return false;
        }

        if (!_check_black_height()) {
            return false;
        }

        return true;
    }
};

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "YES";
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

    if (tree.isRBTree()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}