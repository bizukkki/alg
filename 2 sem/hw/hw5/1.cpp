#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    std::vector<std::vector<bool>> is_edge_;
    int size_;

public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
        is_edge_.assign(n + 1, std::vector<bool>(n + 1, false));
    }
    void AddEdge(Edge e) {
        adj_[e.from].push_back(e);
        is_edge_[e.from][e.to] = true;
    }
    std::vector<Edge>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
    bool IsEdge(int u, int v) {
    return is_edge_[u][v];
    }
};

int main() {
    int n;
    std::cin >> n;
    Graph g(n);
    int inf = 1e9;
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(n+1, 0));
    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < n + 1; j++) {
            int p;
            std::cin >> p;
            if (i == j) {
                dist[i][j] = 0;
            } else if (p) {
                dist[i][j] = 1;
            } else {
                dist[i][j] = inf;
            }
        }
    }
    for (int k = 1; k < n + 1; k++) {
        for (int from = 1; from < n + 1; from++) {
            for (int to = 1; to < n + 1; to++) {
                dist[from][to] = std::min(dist[from][to] , dist[from][k] + dist[k][to]);
            }
        }
    }
    for (int from = 1; from < n + 1; from++) {
        for (int to = 1; to < n + 1; to++) {
            if (dist[from][to] == inf) std::cout << 0 << " ";
            else std::cout << 1 << " "; 
        }
        std::cout << "\n";
    }
}   