#include <iostream>
#include <vector>

class PersisQueue {
private:
    struct Node {
        int val;
    };
    struct QueueState {
        int end_note;
        int len;
    };
    std::vector<Node> tree_nodes;
    std::vector<QueueState> versions;
    std::vector<std::vector<int>> up; 

public:
    PersisQueue(int n) {
        tree_nodes.reserve(n + 1);
        versions.reserve(n + 1);
        up.assign(n + 1, std::vector<int>(18, 0));
        tree_nodes.push_back({0});
        versions.push_back({0, 0});
    }

    void push(int parent_id, int value) {
        QueueState parent = versions[parent_id];
        tree_nodes.push_back({value});
        int new_tail_idx = tree_nodes.size() - 1;
        up[new_tail_idx][0] = parent.end_note;
        for (int i = 1; i < 18; ++i) {
            up[new_tail_idx][i] = up[up[new_tail_idx][i - 1]][i - 1];
        }
        versions.push_back({new_tail_idx, parent.len + 1});
    }

    int pop(int parent_id) {
        QueueState parent = versions[parent_id];
        int steps = parent.len - 1;
        int head_node = parent.end_note;
        for (int i = 0; i < 18; ++i) {
            if ((steps >> i) & 1) {
                head_node = up[head_node][i];
            }
        }
        int deleted_value = tree_nodes[head_node].val;
        if (parent.len - 1 == 0) {
            versions.push_back({0, 0});
        } else {
            versions.push_back({parent.end_note, parent.len - 1});
        }
        return deleted_value;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    PersisQueue q(n);
    for (int i = 1; i <= n; ++i) {
        int type, t;
        std::cin >> type >> t;
        if (type == 1) {
            int m;
            std::cin >> m;
            q.push(t, m);
        } else {
            int a = q.pop(t);
            std::cout << a << "\n";
        }
    }
    return 0;
}
