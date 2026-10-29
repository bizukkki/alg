#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Point{
    int x;
    int y;
};
struct Edge {
    int from;
    int to;
    double weight;
};
class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    int size_;
    std::vector<std::vector<bool>> is_edge_;

public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
        is_edge_.assign(n + 1, std::vector<bool>(n + 1, false));
    }
    void AddEdge(Edge e) {
        adj_[e.from].push_back(e);
        adj_[e.to].push_back({e.to, e.from, e.weight});
        is_edge_[e.from][e.to] = true;
        is_edge_[e.to][e.from] = true;

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
    std::vector<Point> vertexs(n+1);
    Graph g(n);
    for (int i = 1; i < n +1; i++){
        Point p;
        std::cin >> p.x >> p.y;
        vertexs[i] = p;
    } 
    int m;
    std::cin >> m;
    for (int i = 1; i < m + 1; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.AddEdge({v1, v2, 0.0});
    }

    for (int i = 1; i < n +1; i++) {
        Point p = vertexs[i];
        for (int j = 1; j < i; j++){
            if (!g.IsEdge(i, j)) {
                Edge e;
                e.from = j;
                e.to = i;
                Point p1 = vertexs[j];
                double dist = pow((p.x - p1.x), 2) + pow((p.y - p1.y), 2);
                e.weight = pow(dist, 0.5);
                g.AddEdge(e);
            }
        }
    }
    std::vector<bool> used(n+1, false);
    double inf = 10000000000.0;
    std::vector<double> min_edge(n+1, inf);
    min_edge[1] = 0;
    std::vector<int> from_edge(n+1, -1);
    double answer = 0.0;
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
    std::cout << std::fixed << std::setprecision(6)<< answer;
}
