#include <iostream>
#include <vector>
#include <queue>

class Graph {
private:
    std::vector<std::vector<int>> adj_;
    int size_;

public:
    Graph(int n) : size_(n) {
        adj_.resize(n + 1);
    }
    void AddEdge(int from, int to) {
        adj_[from].push_back(to);
    }
    std::vector<int>& GetChildren(int v) {
        return adj_[v];
    }
    int Size() const {
        return size_;
    }
};

void bfs(Graph &g, int start, std::vector<int> &ways) {
    std::queue<int> q;
    ways[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g.GetChildren(v)) {
            if (ways[to] == -1) {
                ways[to] = ways[v] + 1;
                q.push(to);
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    std::vector<std::pair<int,int>> edges;
    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        g.AddEdge(v, u);
        g.AddEdge(u, v);
        edges.push_back({v, u});
    }
    int s, t;
    std::cin >> s >> t;
    std::vector<int> ways_s(n+1, -1);
    bfs(g, s, ways_s);
    std::vector<int> ways_t(n+1, -1);
    bfs(g, t, ways_t);

    int d = ways_s[t];
    int answer = 0;

    for (auto [v, u] : edges) {
        bool flag = false;
        if (ways_s[v] != -1 && ways_t[u] != -1 && ways_s[v] + 1 + ways_t[u] == d) {
            flag = true;
        }
        if (ways_s[u] != -1 && ways_t[v] != -1 && ways_s[u] + 1 + ways_t[v] == d) {
            flag = true;
        }
        if (!flag) answer++;
    }
    std::cout << answer;
}