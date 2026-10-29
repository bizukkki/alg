#include <iostream>
#include <vector>

struct Node {
    int lb;
    int rb;
    long long s = 0;
    long long new_s = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int l, int r) : lb(l), rb(r) {}
};

class cutTree {
public:
    cutTree(int n) {
        arr.resize(n);
        root = new Node(0, n - 1);
    }
    void add(int indx, long long val) {
        arr[indx] = val;
    }
    void build() {
        _build(root);
    }
    long long sum(int l, int r) {
        return _sum(root, l, r);
    }
    void update(int l, int r, long long val) {
        _update(root, l, r, val);
    }

private:
    Node* root = nullptr;
    std::vector<long long> arr;
    void _build(Node* node) {
        int lb = node->lb;
        int rb = node->rb;
        if (lb == rb) {
            node->s = arr[lb];
            return;
        }
        int m = lb + (rb - lb) / 2;
        node->left = new Node(lb, m);
        node->right = new Node(m + 1, rb);
        _build(node->left);
        _build(node->right);
        node->s = node->left->s + node->right->s;
    }

    void push(Node* node) {
        if (node->new_s == 0 || node->lb == node->rb)
            return;

        long long val = node->new_s;

        node->left->s += (node->left->rb - node->left->lb + 1) * val;
        node->right->s += (node->right->rb - node->right->lb + 1) * val;
        node->left->new_s += val;
        node->right->new_s += val;
        node->new_s = 0;
    }

    void _update(Node* node, int l, int r, long long val) {
        if (r < node->lb || l > node->rb)
            return;
        if (l <= node->lb && node->rb <= r) {
            node->s += (node->rb - node->lb + 1) * val;
            node->new_s += val;
            return;
        }
        push(node);
        _update(node->left, l, r, val);
        _update(node->right, l, r, val);
        node->s = node->left->s + node->right->s;
    }

    long long _sum(Node* node, int l, int r) {
        if (r < node->lb || l > node->rb)
            return 0;
        if (l <= node->lb && node->rb <= r)
            return node->s;
        push(node);
        return _sum(node->left, l, r) + _sum(node->right, l, r);
    }
};

int main() {
    int n;
    std::cin >> n;
    cutTree tree(n);
    for (int i = 0; i < n; i++) {
        long long x;
        std::cin >> x;
        tree.add(i, x);
    }
    tree.build();
    int k, type, l, r;
    long long x;
    std::vector<long long> answ;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> l >> r;
            answ.push_back(tree.sum(l, r));
        } else {
            std::cin >> l >> r >> x;
            tree.update(l, r, x);
        }
    }
    for (long long a : answ) std::cout << a << "\n";
}