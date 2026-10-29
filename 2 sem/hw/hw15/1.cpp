#include <iostream>
#include <vector>

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> degrees(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        edges.push_back({a, b});
        degrees[a]++;
        degrees[b]++;
    }
    Graph g(n);
    for (auto e : edges) {
        int a = e.first;
        int b = e.second;
        if (degrees[a] < degrees[b]) {
            g.AddEdge(a, b);
        } else if (degrees[a] > degrees[b]) {
            g.AddEdge(b, a);
        } else {
            if (a < b) {
                g.AddEdge(a, b);
            } else {
                g.AddEdge(b, a);
            }
        }
    }
    std::vector<int> used(n + 1, 0);
    int answer = 0;
    for (int v = 1; v <= g.Size(); v++) {
        for (int to : g.GetChildren(v)) {
            used[to] = v;
        }
        for (int u : g.GetChildren(v)) {
            for (int to : g.GetChildren(u)) {
                if (used[to] == v) {
                    answer++;
                }
            }
        }
    }
    std::cout << answer;
}