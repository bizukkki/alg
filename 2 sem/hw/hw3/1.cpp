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
    q.push(start);
    ways[start] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto to : g.GetChildren(now)) {
            if (ways[to] == -1) {  
                ways[to] = ways[now] + 1;
                q.push(to);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    Graph g(n);
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            int x;
            std::cin >> x;
            if (x) g.AddEdge(i, j);
        }
    }
    int v, u;
    std::cin >> v >> u;
    std::vector<int> ways(n+1, -1);
    bfs(g, v, ways);
    std::cout << ways[u] << "\n";
}