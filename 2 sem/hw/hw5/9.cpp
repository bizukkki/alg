#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
    bool operator>(const Edge& other) const{
        return weight > other.weight;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Edge> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            std::cin >> w;
            if (w != 100000) {
                edges.push_back({i, j, w});
            }
        }
    }
    std::vector<int> dist(n + 1, 0);
    std::vector<int> parent(n + 1, -1);
    int x = -1;
    for (int step = 1; step <= n; ++step) {
        x = -1;
        for (auto e : edges) {
            if (dist[e.to] > dist[e.from] + e.weight) {
                dist[e.to] = dist[e.from] + e.weight;
                parent[e.to] = e.from;
                x = e.to;
            }
        }
    }
    if (x == -1) {
        std::cout << "NO";
        return 0;
    }
    std::vector<int> cycle;
    int cur = x;
    cycle.push_back(cur);
    cur = parent[cur];
    while (cur != x) {
        cycle.push_back(cur);
        cur = parent[cur];
    }
    cycle.push_back(x);
    std::reverse(cycle.begin(), cycle.end());
    std::cout << "YES\n";
    std::cout << cycle.size() << "\n";
    for (int v : cycle) {
        std::cout << v << " ";
    }
}