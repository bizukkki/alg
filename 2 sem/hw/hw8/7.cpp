#include <iostream>
#include <vector>

struct Node {
    int key;
    int prioriry;
    int size = 1;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p) : key(k), prioriry(p) {}
};

class DecTree {
public:
void insert(int key) {
    int priority = std::rand();
    Node* new_node = new Node(key, priority);
    root = merge(root, new_node);
}

void move(int l, int r) {
    std::pair<Node*, Node*> res1 = split(root, r);
    Node* a = res1.first;
    Node* c = res1.second;
    std::pair<Node*, Node*> res2 = split(a, l - 1);
    Node* left = res2.first;
    Node* mid = res2.second;
    root = merge(mid, merge(left, c));
}

void inorder (std::vector<int>& result) {
    _inorder(root, result);
}

private:
Node* root = nullptr;
std::pair<Node*, Node*> split(Node* tree, int k) {
    if (tree == nullptr) return {nullptr, nullptr};
    int left_size = getSize(tree->left);
    if (left_size < k) {
        std::pair<Node*, Node*> res = split(tree->right, k - left_size - 1);
        Node* a = res.first;
        Node* b = res.second;
        tree->right = a;
        update(tree);
        return {tree, b};
    } else {
        std::pair<Node*, Node*> res =split(tree->left, k);
        Node* a = res.first;
        Node* b = res.second;
        tree->left = b;
        update(tree);
        return {a, tree};
    }
}

Node* merge(Node* l, Node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->prioriry > r->prioriry) {
        l->right = merge(l->right, r);
        update(l);
        return l;

    } else {
        r->left = merge(l, r->left);
        update(r);
        return r;
    }
}

int getSize(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    return tree->size;
}

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    tree->size = getSize(tree->left) + getSize(tree->right) + 1;
}

void _inorder(Node* tree, std::vector<int>& result) {
    if (tree == nullptr) {
        return;
    }
    _inorder(tree->left, result);
    result.push_back(tree->key);
    _inorder(tree->right, result);
}
};

int main() {
    DecTree tree;
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i < n + 1; i++) {
        tree.insert(i);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        tree.move(l, r);
    }
    std::vector<int> res;
    tree.inorder(res);
    for (int a : res) std::cout << a << " ";
}