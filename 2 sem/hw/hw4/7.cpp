#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int c;
    int d;
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

int decstra(Graph &g, int start, int finish, int time) {
    int inf = 1e9;
    std::vector<int> dist(g.Size() +1, inf);
    dist[start] = time;
    std::vector<bool> used(g.Size()+1, false);
    for(int i = 1; i < g.Size() + 1; ++i) {
        int v = -1;
        for (int u = 1; u < g.Size() + 1; u++) {
            if ((v == -1 || dist[u] < dist[v]) && !used[u]) v = u;
        }
        if (v == -1) break;
        used[v] = true;
        for (auto ch : g.GetChildren(v)) {
            int to = ch.to;
            int c = ch.c;
            int d = ch.d;
            int wait = (c - dist[v] % c)%c;
            if (dist[to] > dist[v] + wait + d) {
                dist[to] = dist[v] + wait + d;
            }
        }       
    }
    return dist[finish];
}

int main() {
    int inf = 1e9;
    int n, k;
    std::cin >> n >> k;
    Graph g(n);
    for (int i = 1; i < k + 1; i++) {
        Edge e;
        std::cin >> e.from >> e.to >> e.c >> e.d;
        g.AddEdge(e);
    }
    int m;
    std::cin >> m;
    std::vector<int> map;
    for (int i = 0; i < m; i++){
        int point;
        std::cin >> point;
        map.push_back(point);
    }
    int time = 0;
    for (int i = 1; i < m; i++){
        int start = map[i-1];
        int finish = map[i];
        time = decstra(g, start, finish, time);
        if (time == inf){
            std::cout << -1;
            return 0;
        }
    }
    std::cout << time;
}
