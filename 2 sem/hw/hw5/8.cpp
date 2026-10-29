#include <iostream>
#include <vector>

struct Edge {
    int from;
    long long t_from;
    int to;
    long long t_to;
};

int main() {
    int n, a, b, k;
    std::cin >> n >> a >> b >> k;
    std::vector<Edge> edges;
    for (int i = 0; i < k; ++i) {
        Edge e;
        std::cin >> e.from >> e.t_from >> e.to >> e.t_to;
        edges.push_back(e);
    }
    long long inf = 1e18;
    std::vector<long long> dist(n + 1, inf);
    dist[a] = 0;
    for (int i = 0; i < k; ++i) {
        for (auto e : edges) {
            if (dist[e.from] <= e.t_from && dist[e.to] > e.t_to) {
                    dist[e.to] = e.t_to;
                }
            }
        }
    std::cout << dist[b];
}