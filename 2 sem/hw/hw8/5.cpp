#include <iostream>
#include <vector>
#include <string>
struct Node {
    int key;
    int prioriry;
    long long prod;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p) : key(k), prioriry(p), prod(k) {}
};

class DecTree {
public:
void insert(int key) {
    int priority = std::rand();
    Node* new_node = new Node(key, priority);
    std::pair<Node*, Node*> res = split(root, key);
    Node* a = res.first;
    Node* b = res.second;
    root = merge(a, merge(new_node, b));
}

void remove(int key) {
    std::pair<Node*, Node*> res = split(root, key);
    Node* a = res.first;
    Node* b = res.second;
    Node* min_node = findMin(b);
    if (min_node != nullptr && min_node->key == key) {
        b = removeMin(b);
    }
    root = merge(a, b);
}

Node* removeMin(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    if (tree->left == nullptr) {
        Node* right_child = tree->right;
        delete tree;
        return right_child;
    }
    tree->left = removeMin(tree->left);
    update(tree);
    return tree;
}
Node* findMin(Node* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree;
}

long long product(int L, int R) {
    std::pair<Node*, Node*> res1 = split(root, L);
    Node* a = res1.first;
    Node* b = res1.second;
    std::pair<Node*, Node*> res2 = split(b, R + 1);
    Node* c = res2.first;
    Node* d = res2.second;
    long long ans = getProd(c);
    root = merge(a, merge(c, d));
    return ans;
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
    tree->prod = ((getProd(tree->left) * tree->key) % 1000000007 * getProd(tree->right)) % 1000000007;
}
long long getProd(Node* tree) {
    if (tree == nullptr) {
        return 1;
    }
    return tree->prod;
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
            std::cin >> key;
            tree.insert(key);
        } else if (s == "ERASE") {
            std::cin >> key;
            tree.remove(key);
        } else if (s == "PRODUCT") {
            int l, r;
            std::cin >> l >> r;
            res.push_back(tree.product(l, r));
        } 
    }
    for (auto a : res) std::cout << a << "\n";
}