#include <iostream>
#include <vector>

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

int Kruskal(int n, const std::vector<Edge>& edges, int banned_id, std::vector<int>& used_edges) {
    DSU dsu(n);
    int total = 0;
    int count = 0;
    for (const auto& e : edges) {
        if (e.id == banned_id) {
            continue;
        }
        if (!dsu.Check(e.from, e.to)) {
            dsu.Unite(e.from, e.to);
            total += e.weight;
            count++;
            if (banned_id == -1) {
                used_edges.push_back(e.id);
            }
        }
    }
    if (count != n - 1) {
        return 1000000000;
    }
    return total;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        edges.push_back({a, b, c, i});
    }
    std::sort(edges.begin(), edges.end());
    std::vector<int> used_edges;
    int s1 = Kruskal(n, edges, -1, used_edges);
    int s2 = 1000000000;
    std::vector<int> trash;
    for (int banned_id : used_edges) {
        s2 = std::min(s2, Kruskal(n, edges, banned_id, trash));
    }
    std::cout << s1 << " " << s2;
    return 0;
}