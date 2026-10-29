#include <iostream>
#include <vector>
#include <climits>

struct Node {
    int lb;
    int rb;
    std::pair<long long, int> mx;

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

std::pair<long long, int> max_el(int l, int r) { 
    return _max_el(l, r, root); 
}


private:
Node* root = nullptr;
std::vector<long long> arr;

void _build(Node* node) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb){
        node->mx = {arr[rb], rb};
    } else {
        int m = lb + (rb - lb) / 2;
        node->left = new Node(lb, m);
        node->right = new Node(m + 1, rb);
        _build(node->left);
        _build(node->right);
        node->mx = std::max(node->left->mx, node->right->mx);
    }
}

void _update(Node* node, long long val, int indx) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb) {
        node->mx = {val, lb};
        return;
    }
    int m = lb + (rb - lb) / 2;
    if (indx <= m) {
        _update(node->left, val, indx);
    } else {
        _update(node->right, val, indx);
    }
    node->mx = std::max(node->left->mx, node->right->mx);
}
std::pair<long long, int> _max_el(int l, int r, Node* node) {
        if (l <= node->lb && node->rb <= r) return node->mx;
        if (r < node->lb || l > node->rb)   return {LLONG_MIN, -1};
        return std::max(_max_el(l, r, node->left), _max_el(l, r, node->right));
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
    std::vector<int> answ;
    int type, l, r, id;
    long long x;
    for (int i = 0; i < k; i++) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> l >> r;
            answ.push_back( tree.max_el(l, r).second);
        } else if(type == 2) {
            std::cin >> id >> x;
            tree.update(x, id);
        }
    }
    for (long long a : answ) std::cout << a << "\n";
}