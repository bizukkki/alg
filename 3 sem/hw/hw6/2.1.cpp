#include <iostream>
#include <vector>

struct Node {
    int lb;
    int rb;
    int val;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int l, int r) : lb(l), rb(r), val(0) {}
};

class PersisSegmentTree {
public:
    PersisSegmentTree(int size) {
        n = size;
        Node* initial_root = build(0, n);
        version_roots.push_back(initial_root);
    }
    void add_version(int pos) {
        Node* old_root = version_roots.back();
        Node* new_root = update(old_root, pos);
        version_roots.push_back(new_root);
    }
    int get_count(int r, int l) {
        return query(version_roots[r], 0, l - 1);
    }

private:
    int n;
    std::vector<Node*> version_roots;
    Node* build(int l, int r) {
        Node* node = new Node(l, r);
        if (l == r) return node;
        int m = l + (r - l) / 2;
        node->left = build(l, m);
        node->right = build(m + 1, r);
        return node;
    }

    Node* update(Node* old_node, int pos) {
        Node* new_node = new Node(old_node->lb, old_node->rb);
        new_node->val = old_node->val + 1;
        if (old_node->lb == old_node->rb) {
            return new_node;
        }
        int m = old_node->lb + (old_node->rb - old_node->lb) / 2;
        if (pos <= m) {
            new_node->left = update(old_node->left, pos);
            new_node->right = old_node->right;
        } else {
            new_node->left = old_node->left;
            new_node->right = update(old_node->right, pos);
        }

        return new_node;
    }

    int query(Node* node, int ql, int qr) {
        if (qr < node->lb || node->rb < ql) return 0;
        if (ql <= node->lb && node->rb <= qr) return node->val;
        return query(node->left, ql, qr) + query(node->right, ql, qr);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    std::vector<int> last_pos(m + 1, 0);
    PersisSegmentTree tree(n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        int prev = last_pos[a[i]];
        tree.add_version(prev);
        last_pos[a[i]] = i;
    }
    int q;
    std::cin >> q;
    long long p = 0;
    for (int i = 0; i < q; ++i) {
        long long x, y;
        std::cin >> x >> y;
        int l = ((x + p) % n) + 1;
        int k = ((y + p) % m) + 1;
        int low = l;
        int high = n;
        int ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int current_unique = tree.get_count(mid, l) - (l - 1);
            if (current_unique >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        std::cout << ans << "\n";
        p = ans;
    }
}