#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int time;
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
    }
    std::vector<Edge>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

int decstra(Graph &g, int start, int finish, int need) {
    need = 100 * need;
    int inf = 1e9;
    std::vector<int> dist(g.Size() +1, inf);
    dist[start] = 0;
    std::vector<bool> used(g.Size()+1, false);
    for(int i = 1; i < g.Size() + 1; ++i) {
        int v = -1;
        for (int u = 1; u < g.Size() + 1; u++) {
            if ((v == -1 || dist[u] < dist[v]) && !used[u]) v = u;
        }
        if (v == -1 || dist[v] == inf) break;
        used[v] = true;
        for (auto ch : g.GetChildren(v)) {
            if (dist[ch.to] > dist[v] + ch.time && ch.weight >= need) {
                dist[ch.to] = dist[v] + ch.time;
            }
        }      
    }
    return dist[finish];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i){
        Edge e;
        std::cin >> e.from >> e.to >> e.time;
        int w;
        std::cin >> w;
        e.weight = w - 3000000;
        g.AddEdge(e);
        g.AddEdge({e.to, e.from, e.time, e.weight});
    }
    int l = 0;
    int r = 10000000;
    int answer = 0;
    while (l <= r) {
        int mid = (r + l) / 2;
        if (decstra(g, 1, n, mid) <= 1440){
            answer = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    std::cout << answer;
}