#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
private:
    std::vector<int> parent_;
    std::vector<int> weight_;

public:
    DSU(int n) {
        parent_.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent_[i] = i;
        }
        weight_.assign(n + 1, 1);
    }
    int Leader(int v) {
        if (v == parent_[v]) return v;
        return parent_[v] = Leader(parent_[v]);
    }
    void Unite(int a, int b) {
        a = Leader(a);
        b = Leader(b);
        if (a == b) return;
        if (weight_[a] < weight_[b]) std::swap(a, b);
        parent_[b] = a;
        weight_[a] += weight_[b];
    }
    bool Check(int a, int b) {
        a = Leader(a);
        b = Leader(b);
        return a==b;
    }
};
struct Edge {
    int from;
    int to;
    int weight;
    int id;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    for (int i = 1; i < m + 1; ++i) {
        Edge e;
        std::cin >> e.from >> e.to >> e.weight;
        edges.push_back(e);
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(n);
    long long answer = 0;
    for (const auto& e : edges) {
        if (!dsu.Check(e.from, e.to)) {
            dsu.Unite(e.from, e.to);
            answer += e.weight;
        }
    }
    std::cout << answer;
}