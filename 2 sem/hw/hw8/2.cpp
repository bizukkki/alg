#include <iostream>
#include <vector>
#include <string>
struct Node {
    int key;
    int prioriry;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int k, int p) : key(k), prioriry(p) {}
};

class DecTree {
public:
int height() {
    return _height(root);
}
int edgeLength(int key) {
    return _edgeLength(root, key, 0);
}
void insert(int key, int prior) {
    Node* new_node = new Node(key, prior);
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
    clear(res2.first);
}

void clear(Node* tree) {
        if (tree == nullptr) {
            return;
        }

        clear(tree->left);
        clear(tree->right);

        delete tree;
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
        return {tree, b};

    } else {
        std::pair<Node*, Node*> res = split(tree->left, key);
        Node* a = res.first;
        Node* b = res.second;
        tree->left = b;
        return {a, tree};
    }
}

Node* merge(Node* l, Node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (l->prioriry > r->prioriry) {
        l->right = merge(l->right, r);
        return l;
    } else {
        r->left = merge(l, r->left);
        return r;
    }
}

int _height(Node* tree) {
    if (tree == nullptr) {
        return 0;
    }
    int left_height = _height(tree->left);
    int right_height = _height(tree->right);
    return std::max(left_height, right_height) + 1;
}

int _edgeLength(Node* tree, int key, int dist) {
    if (tree == nullptr) return -1;
    if (tree->key == key) return dist;
    if (key < tree->key) {
        return _edgeLength(tree->left, key, dist + 1);
    } else {
        return _edgeLength(tree->right, key, dist + 1);
    }
}
};

int main() {
    class DecTree tree;
    int n;
    std::cin >> n;
    std::string s;
    int key, priopity;
    std::vector<int> res;
    for (int i = 0; i < n; i++){
        std::cin >> s;
        if (s == "INSERT"){
            std:: cin>> key >> priopity;
            tree.insert(key, priopity);
        } else if (s == "CONTAINS") {
            std::cin >> key;
            res.push_back(tree.edgeLength(key));
        } else if (s == "ERASE") {
            std::cin >> key;
            tree.remove(key);
        }
    }
    for (auto a : res) std::cout << a << "\n";
}