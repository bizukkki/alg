#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    bool used = false;
};
struct neigbour{
    int to;
    int id;
};

class Graph {
private:
    std::vector<std::vector<neigbour>> adj_;
    int size_;
    std::vector<Edge> edges_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to, int id) {
        adj_[from].push_back({to, id});
        adj_[to].push_back({from, id});
        edges_.push_back({from, to, false});
    }
    std::vector<neigbour>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
    std::vector<Edge>& GetEdges() {
        return edges_;
    }
};

void dfs (Graph &g, int now, int edge_parent,
         std::vector<int> &tin, std::vector<int> &up,
         bool &flag, int &time) {
    ++time;
    tin[now] = time;
    up[now] = time;
    for (auto neib : g.GetChildren(now)) {
        int to = neib.to;
        int id = neib.id;
        Edge &e = g.GetEdges()[id];
        if (!e.used) {
            e.from = now;
            e.to = to;
            e.used = true;
        }
        if (id == edge_parent) continue;
        if (tin[to]) {
            up[now] = std::min(up[now], tin[to]);
        } else {
            dfs(g, to, id, tin, up, flag, time);
            up[now] = std::min(up[now], up[to]);
            if (up[to] > tin[now]) flag = false;
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
        g.AddEdge(v1, v2, i);
    }
    bool flag = true;
    std::vector<int> tin(n+1, 0);
    std::vector<int> up(n+1, 0);
    std::vector<bool> used(m+1, false);
    int time = 0;
    for (int now = 1; now < n + 1; ++now) {
        if (tin[now] == 0) {
            dfs(g, now, -1, tin, up, flag, time);
        }
    }
    if (flag) {
        for (auto e : g.GetEdges()) {
                std::cout << e.from << " " << e.to << std::endl;
        }
    } else std::cout << 0;
} 
