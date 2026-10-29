#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

void Dfs(int v, std::vector<std::vector<int>>& g, std::vector<bool>& used) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            Dfs(to, g, used);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> rev_g(n + 1);
    for (int i = 0; i < m; ++i) {
        Edge e;
        std::cin >> e.from >> e.to >> e.weight;
        edges.push_back(e);
        rev_g[e.to].push_back(e.from);
    }
    std::vector<bool> dfs_f(n + 1, false);
    Dfs(n, rev_g, dfs_f);
    long long NEG_INF = -1 * 1e13;
    std::vector<long long> dist(n + 1, NEG_INF);
    dist[1] = 0;
    for (int k = 1; k <  n; ++k) {
        for (auto e : edges) {
            if (dist[e.from] != NEG_INF && dist[e.to] < dist[e.from] + e.weight) {
                dist[e.to] = dist[e.from] + e.weight;
            }
        }
    }
    for (auto e : edges) {
        if (dist[e.from] != NEG_INF && dist[e.to] < dist[e.from] + e.weight && dfs_f[e.to]) {
            std::cout << ":)";
            return 0;
        }
    }
    if (dist[n] == NEG_INF) std::cout << ":(";
    else std::cout << dist[n];
}