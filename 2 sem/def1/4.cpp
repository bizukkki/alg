#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

// class Graph {
// private:
//     std::vector<std::vector<Edge>> adj_;
//     int size_;

// public:
//     Graph(int n) : size_(n) {
//         adj_.resize(n + 1);
//     }
//     void AddEdge(Edge e) {
//         adj_[e.from].push_back(e);
//     }
//     std::vector<Edge>& GetChildren(int v) {
//         return adj_[v];
//     }
//     int Size() const {
//         return size_;
//     }
// };

int main() {
    int n, m;
    std::cin >> n >> m;
    // Graph g(n);
    int inf = 1e9;
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(n+1, inf));
    // std::vector<int> city1;
    // std::vector<int> city2;
    std::vector<int> city(n +1, 0);
    for (int i = 1; i < n +1; i++) {
        int c;
        std::cin >> c;
        city[i] = c;
        // if (c == 1) city1.push_back(i);
        // else if (c == 2) city2.push_back(i);
    }
    for (int i = 1; i < m + 1; i++) {
        Edge e;
        std::cin >> e.from >> e.to >> e.weight;
        // g.AddEdge(e);
        // g.AddEdge({e.to, e.from, e.weight});
        dist[e.from][e.to] = e.weight;
        dist[e.to][e.from] = e.weight;
    }
    for (int i = 1; i < n +1; i++) {
        dist[i][i] = 0;
    }
    int min_dist = inf;
    for (int k = 1; k < n + 1; k++) {
        for (int from = 1; from < n + 1; from++) {
            for (int to = 1; to < n + 1; to++) {
                dist[from][to] = std::min(dist[from][to], dist[from][k] + dist[k][to]);
                if ((city[from] == 1 && city[to] == 2) || (city[from] == 2 && city[to] == 1)) {
                    min_dist = std::min(min_dist, dist[from][to]);
                }
            }
        }
    }
    // for (auto c1 : city1) {
    //     for (auto c2 : city2) {
    //         min_dist = std::min(min_dist, std::min(dist[c1][c2], dist[c2][c1]));
    //     }
    // }
    if (min_dist == inf) std::cout << -1;
    else std::cout << min_dist;

}   