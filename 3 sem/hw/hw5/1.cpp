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

bool backtrack(Graph &g, int v, int s, int k, std::vector<int> &bad) {
    if (k == s) {
        return true;
    }
    if (k + (g.Size() - v + 1) < s) {
        return false;
    }
    if (v > g.Size()) {
        return false;
    }
    if (bad[v] == 0) {
        for (int ch : g.GetChildren(v)) {
            bad[ch]++;
        }
        if (backtrack(g, v + 1, s, k + 1, bad)) {
            return true; 
        }
        for (int ch : g.GetChildren(v)) {
            bad[ch]--;
        }
    }
    if (backtrack(g, v + 1, s, k, bad)) {
        return true;
    }
    return false;
}

int main() {
    int v, s, e;
    std::cin >> v >> s >> e;
    Graph g(v);
    for (int i = 0; i < e; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u != v) {
            g.AddEdge(u, v);
            g.AddEdge(v, u);
        }
    }
    std::vector<int> bad(v + 1, 0);
    if (backtrack(g, 1, s, 0, bad)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
