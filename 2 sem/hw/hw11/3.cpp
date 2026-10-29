#include <iostream>
#include <vector>

class Graph {
private:
    std::vector<std::vector<int>> adj_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to) {
        adj_[from].push_back(to);
    }
    std::vector<int>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void dfs (Graph &g, int now, std::vector<int> &tin, std::vector<int> &tout, int &time, std::vector<int> &depth, 
    std::vector<std::vector<int>> &levels ) {
    ++time;
    tin[now] = time;
    for (auto ch : g.GetChildren(now)) {
        depth[ch] = depth[now] + 1;
        dfs(g, ch, tin, tout, time, depth, levels);
    }
    time++;
    tout[now] = time;
    levels[depth[now]].push_back(tin[now]);
}
int main () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Graph g(n);
    int root, p;
    for (int i = 1; i < n + 1; i++) {
        std::cin >> p;
        if (p == -1) root = i;
        else g.AddEdge(p, i);
    }
    std::vector<int> depth(n+1, 0);
    std::vector<int> tin(n+1);
    std::vector<int> tout(n+1);
    std::vector<std::vector<int>> levels(n + 1);
    int time = 0;
    dfs(g, root, tin, tout, time, depth, levels);
    int m, v, k;
    std::cin >> m;
    std::vector<int> answer;
    for (int i = 0; i < m; i++){
        std::cin >> v >> k;
        int need_depth = depth[v] + k;
        if (need_depth > n) {
            answer.push_back(0);
            continue;
        }
        std::vector<int>& cur = levels[need_depth];
        auto left = std::lower_bound(cur.begin(), cur.end(), tin[v]);
        auto right = std::lower_bound(cur.begin(), cur.end(), tout[v]);
        answer.push_back(right - left);
    }
    for (auto a : answer) std::cout << a << "\n";
}