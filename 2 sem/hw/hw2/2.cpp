#include <iostream>
#include <vector>

struct neigbour{
    int to;
    int id;
};

class Graph {
private:
    std::vector<std::vector<neigbour>> adj_;
    int size_;
public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to, int id) {
        neigbour neib;
        neib.to = to;
        neib.id = id;
        adj_[from].push_back(neib);
        neib.to = from;
        adj_[to].push_back(neib);

    }
    std::vector<neigbour>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void dfs (Graph &g, int now, int edge_parent,
         std::vector<int> &tin, std::vector<int> &up,
         std::vector<bool> &bridge, int &time) {
    ++time;
    tin[now] = time;
    up[now] = time;
    for (auto neib : g.GetChildren(now)) {
        int to = neib.to;
        int id = neib.id;
        if (id == edge_parent) continue;
        if (tin[to]) {
            up[now] = std::min(up[now], tin[to]);
        } else {
            dfs(g, to, id, tin, up, bridge, time);
            up[now] = std::min(up[now], up[to]);
            if (up[to] > tin[now]) bridge[id] = true;
        }
    }
}
int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 1; i < m + 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2, i);
    }
    std::vector<bool> bridge(m+1, false);
    std::vector<int> tin(n+1, 0);
    std::vector<int> up(n+1, 0);
    int time = 0;
    for (int now = 1; now < n + 1; ++now) {
        if (tin[now] == 0) {
            dfs(g, now, -1, tin, up, bridge, time);
        }
    }
    std::vector<int> answer;
    for (int i = 1; i < m + 1; ++i) {
        if (bridge[i]) {
            answer.push_back(i);
        }
    }
    std::cout << answer.size() << std::endl;
    for (int v : answer) {
        std::cout << v << " ";
    }
}