#include <iostream>
#include <vector>
#include <string>
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
int get(int index) {
    if (index < 0 || index >= getSize(root)) {
        return -1;
    }
    return _get(root, index);
}
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

int _get(Node* tree, int index){
    int left_size = getSize(tree->left);
    if (index < left_size) {
        return _get(tree->left, index);
    }
    if (index == left_size) {
        return tree->key;
    }
    return _get(tree->right, index - left_size - 1);
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
        std::cin >> s >> key;
        if (s == "INSERT"){
            tree.insert(key);
        } else if (s == "ERASE") {
            tree.remove(key);
        } else if (s == "GET") {
            res.push_back(tree.get(key));
        } 
    }
    for (auto a : res) std::cout << a << "\n";
}