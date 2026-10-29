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

void dfs (Graph &g, int now, int parent,
         std::vector<int> &tin, std::vector<int> &up,
         std::vector<bool> &point, int &time) {
    ++time;
    tin[now] = time;
    up[now] = time;
    int ch_dfs = 0;
    for (auto to : g.GetChildren(now)) {
        if (to == parent) continue;
        if (tin[to]) {
            up[now] = std::min(up[now], tin[to]);
        } else {
            ch_dfs++;
            dfs(g, to, now, tin, up, point, time);
            up[now] = std::min(up[now], up[to]);
            if (parent!=-1 && up[to] >= tin[now]) point[now] = true;
        }
    }
    if (parent == -1 && ch_dfs > 1) point[now] = true;
}
int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2);
        g.AddEdge(v2, v1);
    }
    std::vector<bool> point(n+1, false);
    std::vector<int> tin(n+1, 0);
    std::vector<int> up(n+1, 0);
    int time = 0;
    for (int now = 1; now < n + 1; ++now) {
        if (tin[now] == 0) {
            dfs(g, now, -1, tin, up, point, time);
        }
    }
    std::vector<int> answer;
    for (int v = 1; v < n + 1; ++v) {
        if (point[v]) {
            answer.push_back(v);
        }
    }
    std::cout << answer.size() << std::endl;
    for (int v : answer) {
        std::cout << v << std::endl;
    }
}