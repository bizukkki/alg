#include <iostream>
#include <vector>
#include <climits>

struct Node {
    int key;
    int priority;
    int size = 1;
    int minVal;
    bool rev = false;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p) : key(k), priority(p), minVal(k) {}
};

class DecTree {
public:
    void insert(int key) {
        int priority =  std::rand();
        Node* new_node = new Node(key, priority);
        root = merge(root, new_node);
    }

    void reverse(int l, int r) {
        auto [left, mid_right] = split(root, l - 1);
        auto [mid, right] = split(mid_right, r - l + 1);
        if (mid) mid->rev ^= true;
        root = merge(left, merge(mid, right));
    }

    int Min(int l, int r) {
        auto [left, mid_right] = split(root, l - 1);
        auto [mid, right] = split(mid_right, r - l + 1);
        int ans = getMin(mid);
        root = merge(left, merge(mid, right));
        return ans;
    }

private:
    Node* root = nullptr;
    int getSize(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->size;
}
    int getMin(Node* tree) {
        if (tree == nullptr) {
            return INT_MAX;
        }
        return tree->minVal; 
    }

    void push(Node* tree) {
        if (tree == nullptr|| !tree->rev) return;
        std::swap(tree->left, tree->right);
        if (tree->left)  tree->left->rev = tree->left->rev ^ 1;
        if (tree->right) tree->right->rev = tree->right->rev ^ 1;
        tree->rev = false;
    }

    void update(Node* tree) {
        if (tree == nullptr) return;
        tree->size = getSize(tree->left) + getSize(tree->right) + 1;
        tree->minVal = std::min(tree->key, std::min(getMin(tree->left), getMin(tree->right)));
    }

    std::pair<Node*, Node*> split(Node* tree, int k) {
        if (tree == nullptr) return {nullptr, nullptr};
        push(tree);
        int leftSize = getSize(tree->left);
        if (leftSize >= k) {
            std::pair<Node*, Node*> res = split(tree->left, k);
            Node* a = res.first;
            Node* b = res.second;
            tree->left = b;
            update(tree);
            return {a, tree};
        } else {
            std::pair<Node*, Node*> res = split(tree->right, k - leftSize - 1);
            Node* a = res.first;
            Node* b = res.second;
            tree->right = a;
            update(tree);
            return {tree, b};
        }
    }

    Node* merge(Node* l, Node* r) {
        if (l == nullptr) return r;
        if (r == nullptr) return l;
        push(l); 
        push(r);
        if (l->priority > r->priority) {
            l->right = merge(l->right, r);
            update(l);
            return l;
        } else {
            r->left = merge(l, r->left);
            update(r);
            return r;
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    DecTree tree;
    for (int i = 0; i < n; i++) {
        int a; std::cin >> a;
        tree.insert(a);
    }
    std::vector<int> res;
    for (int i = 0; i < m; i++) {
        int type, l, r;
        std::cin >> type >> l >> r;
        if (type == 1) {
            tree.reverse(l, r);
        } else {
            res.push_back(tree.Min(l, r));
        }
    }
    for (int a : res) std::cout << a << "\n";
}