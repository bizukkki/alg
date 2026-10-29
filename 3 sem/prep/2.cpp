#include <iostream>
#include <vector>

struct Node {
    std::vector<Node*> to;
    int value = -1;
    Node() {
        to.resize(2, nullptr);
    }
};

class Tree {
private:
    Node* root;
public:
    Tree() {
        root = new Node;
    }
    void add(int num) {
        Node* runner = root;
        for (int i = 29; i >= 0; i--) {
            int bit = (num >> i) & 1; 
            if (runner->to[bit] == nullptr) {
                runner->to[bit] = new Node;
            }
            runner = runner->to[bit];
        }
        runner->value = num;
    }

    int get_max_xor_pair(int num) {
        Node* runner = root;
        for (int i = 29; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int desired_bit = 1 - bit;
            if (runner->to[desired_bit] != nullptr) {
                runner = runner->to[desired_bit];
            } else {
                runner = runner->to[bit];
            }
        }
        return runner->value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    Tree tree;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        tree.add(a);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int b;
        std::cin >> b;
        std::cout << tree.get_max_xor_pair(b) << '\n';
    }
    return 0;
}
