#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

struct Node {
    int lb;
    int rb;
    int count;
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
int count_ch(int l, int r) {
    return _count_ch(l, r, root);
}

void update(int val, int indx) {
    int dif = (1 - std::abs(val) % 2) - (1 - std::abs(arr[indx]) % 2);
    arr[indx] = val;
    if (dif!=0) {
        _update(root, dif, indx);
    }

}
int find(int l, int r, int k) {
    if (_count_ch(l, r, root) < k) return INT_MIN;
    return _find(root, l, r, k);
}

private:
Node* root = nullptr;
std::vector<int> arr;

void _build(Node* node) {
    int lb = node->lb;
    int rb = node->rb;
    if (lb == rb){
        node->count = 1 - std::abs(arr[rb]) % 2;
    } else {
        int m = lb + (rb - lb) / 2;
        node->left = new Node(lb, m);
        node->right = new Node(m + 1, rb);
        _build(node->left);
        _build(node->right);
        node->count = node->left->count + node->right->count;
    }
}

void _update(Node* node, int val, int indx) {
    node->count += val;
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
int _count_ch(int l, int r, Node* node) {
    if (l <= node->lb && node->rb <= r) {
        return node->count;
    }
    if (r < node->lb || l > node->rb) {
        return 0;
    }
    return _count_ch(l, r, node->left) + _count_ch(l, r, node->right);
}

int _find(Node* node, int l, int r, int k) {
    if (node->lb == node->rb) return arr[node->lb];
    int left_count = _count_ch(l, r, node->left);
    if (left_count >= k)
        return _find(node->left,  l, r, k);
    else
        return _find(node->right, l, r, k - left_count);
    }
};

int main() {
    int n;
    std::cin >> n;
    cutTree tree(n);
    int a;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        tree.add(i, a);
    }
    tree.build();
    int k;
    std::cin >> k;
    std::vector<int> answ;
    int type, l, r, q, id, x;
    for (int i = 0; i < k; i++) {
        std::cin >> type;
        if (type == 1) {
            std::cin >> l >> r >> q;
            int a = tree.find(l, r, q);
            if (a == INT_MIN) std::cout << "NONE" << "\n";
            else std::cout<< a << "\n";
        } else if(type == 2) {
            std::cin >> id >> x;
            tree.update(x, id);
        }
    }
}