#include <iostream>
#include <vector>
#include <string>
struct Node {
    int key;
    int value;
    int prioriry;
    int max_val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p, int v) : key(k), value(v), prioriry(p), max_val(v)  {}
};

class DecTree {
public:
void insert(int key, int value) {
    int priority = std::rand();
    Node* new_node = new Node(key, priority, value);
    std::pair<Node*, Node*> res = split(root, key);
    Node* a = res.first;
    Node* b = res.second;
    root = merge(a, merge(new_node, b));
}

void remove(int key) {
    std::pair<Node*, Node*> res = split(root, key);
    Node* a = res.first;
    Node* b = res.second;
    std::pair<Node*, Node*> res2 = split(b, key + 1);
    Node* c = res2.second;
    root = merge(a, c);
}

int maxval(int L, int R) {
    std::pair<Node*, Node*> res1 = split(root, L);
    Node* a = res1.first;
    Node* b = res1.second;
    std::pair<Node*, Node*> res2 = split(b, R + 1);
    Node* c = res2.first;
    Node* d = res2.second;
    int ans = getMax(c);
    root = merge(a, merge(c, d));
    return ans;
}
int getMax(Node* tree) {
    if (tree == nullptr) {
        return -1;
    }
    return tree->max_val;
}

private:
Node* root = nullptr;
std::pair<Node*, Node*> split(Node* tree, int key) {
    if (tree == nullptr) return {nullptr, nullptr};
    if (tree->key < key) {
        std::pair<Node*, Node*> res = split(tree->right, key);
        Node* a = res.first;
        Node* b = res.second;
        tree->right = a;
        update(tree);
        return {tree, b};

    } else {
        std::pair<Node*, Node*> res = split(tree->left, key);
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

void update(Node* tree) {
    if (tree == nullptr) {
        return;
    }
    tree->max_val = std::max(tree->value, std::max(getMax(tree->left), getMax(tree->right)));
}
};

int main() {
    class DecTree tree;
    int n;
    std::cin >> n;
    std::string s;
    int key;
    std::vector<int> res;
    for (int i = 0; i < n; i++){
        std::cin >> s;
        if (s == "INSERT"){
            int prior;
            std::cin >> key >> prior;
            tree.insert(key, prior);
        } else if (s == "ERASE") {
            std::cin >> key;
            tree.remove(key);
        } else if (s == "MAXVAL") {
            int l, r;
            std::cin >> l >> r;
            res.push_back(tree.maxval(l, r));
        } 
    }
    for (auto a : res) std::cout << a << "\n";
}