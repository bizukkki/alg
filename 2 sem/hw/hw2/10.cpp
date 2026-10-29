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
         std::vector<bool> &point, int &time, std::vector<bool> &has_v, int v) {
    ++time;
    tin[now] = time;
    up[now] = time;
    if (now == v) has_v[now] = true;
    else has_v[now] = false;
    for (auto to : g.GetChildren(now)) {
        if (to == parent) continue;
        if (tin[to]) {
            up[now] = std::min(up[now], tin[to]);
        } else {
            dfs(g, to, now, tin, up, point, time, has_v, v);
            up[now] = std::min(up[now], up[to]);
            if (has_v[to]) has_v[now] = true; 
            if (has_v[to] && up[to] >= tin[now]) point[now] = true;
        }
    }
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
    int u, v;
    std::cin >> u >> v;
    std::vector<bool> point(n+1, false);
    std::vector<int> tin(n+1, 0);
    std::vector<int> up(n+1, 0);
    std::vector<bool> has_v(n+1, false);
    int time = 0;
    dfs(g, u, -1, tin, up, point, time, has_v, v);
    std::vector<int> answer;
    for (int i = 1; i < n + 1; ++i) {
        if (point[i]) {
            answer.push_back(i);
        }
    }
    std::cout << answer.size() - 1 << std::endl;
    for (int i : answer) {
        if (i != u) std::cout << i << std::endl;
    }

}