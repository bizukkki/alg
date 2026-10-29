#include <iostream>
#include <vector>

class PersisSegmentTree {
private:
    struct Node {
        int left;
        int right;
        int val;
    };
    std::vector<Node> tree_nodes;
    std::vector<int> version_roots;
    int n;

    int build(int l, int r) {
        int cur_index = tree_nodes.size();
        tree_nodes.push_back({0, 0, 0});
        if (l == r){
            return cur_index;
        }
        int mid = l + (r - l) / 2;
        tree_nodes[cur_index].left = build(l, mid);
        tree_nodes[cur_index].right = build(mid + 1, r);
        return cur_index;
    }

    int update(int old_root, int l, int r, int pos) {
        Node old_node = tree_nodes[old_root]; 
        int cur_index = tree_nodes.size();
        tree_nodes.push_back(old_node);
        tree_nodes[cur_index].val++;
        if (l == r){
            return cur_index;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            int new_left = update(old_node.left, l, mid, pos);
            tree_nodes[cur_index].left = new_left;
        } else {
            int new_right = update(old_node.right, mid + 1, r, pos);
            tree_nodes[cur_index].right = new_right;
        }
        return cur_index;
    }

    int query(int root, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0; 
        if (ql <= l && r <= qr) return tree_nodes[root].val; 
        int mid = l + (r - l) / 2;
        return query(tree_nodes[root].left, l, mid, ql, qr) + 
               query(tree_nodes[root].right, mid + 1, r, ql, qr);
    }

public:
    PersisSegmentTree(int size) {
        n = size;
        tree_nodes.reserve(2 * n + n * 20);
        version_roots.push_back(build(0, n));
    }

    void add_version(int pos) {
        int new_root = update(version_roots.back(), 0, n, pos);
        version_roots.push_back(new_root);
    }

    int get_unique_count(int r, int l) {
        return query(version_roots[r], 0, n, 0, l - 1);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n + 1);
    std::vector<int> last_pos(m + 1, 0);
    PersisSegmentTree pst(n);
    for (int i = 1; i < n + 1; i++) {
        std::cin >> a[i];
        int prev = last_pos[a[i]]; 
        pst.add_version(prev);
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
            int current_unique = pst.get_unique_count(mid, l) - (l - 1);
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