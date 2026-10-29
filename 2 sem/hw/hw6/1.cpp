#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    int size_;

public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(Edge e) {
        adj_[e.from].push_back(e);
        adj_[e.to].push_back({e.to, e.from, e.weight});
    }
    std::vector<Edge>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};
int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    Graph g(n);
    for (int i = 1; i < m +1; i++){
        Edge e;
        std::cin >> e.from >> e.to >> e.weight;
        g.AddEdge(e);
    } 
    std::vector<bool> used(n+1, false);
    int inf = 1e9;
    std::vector<int> min_edge(n+1, inf);
    min_edge[1] = 0;
    std::vector<int> from_edge(n+1, -1);
    int answer = 0;
    for (int i = 1; i < n+1; i++) {
        int min_vertex = -1;
        for (int v = 1; v < n +1;v++) {
            if (used[v] == false && (min_vertex == -1 || min_edge[min_vertex] > min_edge[v])){
                min_vertex = v;
            }
        }
        used[min_vertex] = true;
        answer += min_edge[min_vertex];
        for (auto e : g.GetChildren(min_vertex)) {
            if (!used[e.to] && e.weight < min_edge[e.to]) {
                min_edge[e.to] = e.weight;
                from_edge[e.to] = min_vertex;
            }
        }
    }
    std::cout << answer;
}
