#include <iostream>
#include <vector>
#include <climits>

struct Node {
    int lb;
    int rb;
    int mx;
    int mn;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int l, int r) : lb(l), rb(r) {}
};

class cutMaxTree {
public:

cutMaxTree(int n) {
    arr.resize(n);
    root = new Node(0, n - 1);
}
void add(int indx, long long val) {
    arr[indx] = val;
}

void build() {
    _build(root);
}

void update(long long val, int indx) {
    arr[indx] = val;
    _update(root, val, indx);
}

int min_el(int l, int r, int elem) { 
    return _min_el(root, l, r, elem); 
}

private:
Node* root = nullptr;
std::vector<long long> arr;

void _build(Node* node) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb){
        node->mx = arr[rb];
        node->mn = arr[rb];
    } else {
        int m = lb + (rb - lb) / 2;
        node->left = new Node(lb, m);
        node->right = new Node(m + 1, rb);
        _build(node->left);
        _build(node->right);
        node->mx = std::max(node->left->mx, node->right->mx);
        node->mn = std::min(node->left->mn, node->right->mn);
    }
}

void _update(Node* node, long long val, int indx) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb) {
        node->mx = val;
        node->mn = val;
        return;
    }
    int m = lb + (rb - lb) / 2;
    if (indx <= m) {
        _update(node->left, val, indx);
    } else {
        _update(node->right, val, indx);
    }
    node->mx = std::max(node->left->mx, node->right->mx);
    node->mn = std::min(node->left->mn, node->right->mn);
}

int _min_el(Node* node, int l, int r, int x) {
    if (!node) return INT_MAX;
    if (r < node->lb || l > node->rb || node->mx <= x)
        return INT_MAX;
    if (l <= node->lb && node->rb <= r && node->mn > x)
        return node->mn;
    if (node->lb == node->rb)
        return node->mn;
    int left = _min_el(node->left, l, r, x);
    if (left != INT_MAX)
        return left;
    return _min_el(node->right, l, r, x);
}
};

int main() {
    int n;
    std::cin >> n;
    cutMaxTree tree(n);
    long long a;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        tree.add(i, a);
    }
    tree.build();
    int k;
    std::cin >> k;
    std::vector<long long> answ;
    int type, l, r, id, x;
    for (int i = 0; i < k; i++) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> l >> r >> x;
            answ.push_back(tree.min_el(l, r, x));
        } else if(type == 2) {
            std::cin >> id >> x;
            tree.update(x, id);
        }
    }
    for (int a : answ){
        if (a == INT_MAX) std::cout << "NONE\n";
        else std::cout << a << "\n";
    }
}