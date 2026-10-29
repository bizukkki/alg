#include <iostream>
#include <vector>

struct Edge {
    int from;
    int t_from;
    int to;
    int t_to;
};

int main() {
    int n;
    std::cin >> n;
    int start, finish;
    std::cin >> start >> finish;
    int r;
    std::cin >> r;
    std::vector<std::vector<Edge>> g(n+1);
    for (int i = 1; i < r + 1; i++) {
        Edge e;
        std::cin >> e.from >> e.t_from >> e.to >> e.t_to;
        g[e.from].push_back(e);
    }
    int inf = 1e9;
    std::vector<int> dist(n+1, inf);
    dist[start] = 0;
    std::vector<bool> used(n+1, false);
    for(int i = 1; i < n + 1; ++i) {
        int v = -1;
        for (int u = 1; u < n + 1; u++) {
            if ((v == -1 || dist[u] < dist[v]) && !used[u]) v = u;
        }
        if (v == -1) break;
        used[v] = true;
        for (auto ch : g[v]) {
            if (dist[ch.to] > ch.t_to && dist[v] <= ch.t_from) {
                dist[ch.to] = ch.t_to;
            }
        }
    }
    if (dist[finish] != inf) std::cout << dist[finish];
    else std::cout << -1;
}