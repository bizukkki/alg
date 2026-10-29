#include <iostream>
#include <vector>

struct Node {
    int lb;
    int rb;
    long long s;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int l, int r) : lb(l), rb(r), s(0) {}
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
    return _sum(l, r, root);
}

void update(long long val, int indx) {
    long long dif = val - arr[indx];
    if (dif != 0) {
        arr[indx] = val;
        _update(root, dif, indx);
    }
}
int find_pref(long long s) {
    if (root->s < s) return -1;
    if (s == 0) return 0;
    return _find_pref(root, s);
}


private:
Node* root = nullptr;
std::vector<long long> arr;

void _build(Node* node) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb){
        node->s = arr[rb];
    } else {
        int m = lb + (rb - lb) / 2;
        node->left = new Node(lb, m);
        node->right = new Node(m + 1, rb);
        _build(node->left);
        _build(node->right);
        node->s = node->left->s + node->right->s;
    }
}

void _update(Node* node, long long val, int indx) {
    node->s +=val;
    int lb = node->lb;
    int rb = node->rb;
    if (lb == indx && rb == indx) return;
    int m = lb + (rb - lb) / 2;
    if (indx <= m) {
        _update(node->left, val, indx);
    } else {
        _update(node->right, val, indx);
    }
}
long long _sum(int l, int r, Node* node) {
    if (l <= node->lb && node->rb <= r) {
        return node->s;
    }
    if (r < node->lb || l > node->rb) {
        return 0;
    }
    return _sum(l, r, node->left) + _sum(l, r, node->right);
}
int _find_pref(Node* node, long long s) {
    if (node->lb == node->rb) {
        return node->rb + 1;
    }
    if (node->left->s >= s) {
        return _find_pref(node->left, s);
    } else {
        return _find_pref(node->right, s - node->left->s);
    }
}
};

int main() {
    int n;
    std::cin >> n;
    cutTree tree(n);
    long long a;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        tree.add(i, a);
    }
    tree.build();
    int k;
    std::cin >> k;
    std::vector<long long> answ;
    int type, id;
    long long s, x;
    for (int i = 0; i < k; i++) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> s;
            answ.push_back(tree.find_pref(s));
        } else if(type == 2) {
            std::cin >> id >> x;
            tree.update(x, id);
        }
    }
    for (long long a : answ){
        if (a == -1) std::cout << "NONE\n";
        else std::cout << a << "\n";
    }
}