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
        weight_.assign(n+1, 1);
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
    int i;
    int j;
    int d;
    bool operator < (const Edge& other) const{
        return d < other.d;
    }
};

int id(int i, int j, int m) {
    return i*m - m + j;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    DSU dsu(n * m);
    std::vector<Edge> edges;
    for (int i = 1; i  < n +1; ++i) {
        for (int j = 1; j < m +1; ++j) {
            int d;
            std::cin >> d;
            if (d == 1 || d == 3) {
                if (i < n) dsu.Unite(id(i, j, m), id(i + 1, j, m));
            }
            if (d == 2 || d == 3) {
                if (j < m) dsu.Unite(id(i, j, m), id(i, j + 1, m));
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m +1; ++j) {
            edges.push_back({i, j, 1});
        }
    }
    for (int i = 1; i < n +1; ++i) {
        for (int j = 1; j < m; ++j) {
            edges.push_back({i, j, 2});
        }
    }
    std::sort(edges.begin(), edges.end());

    std::vector<Edge> added;
    int total_cost = 0;

    for (const auto& e : edges) {
        int u = id(e.i, e.j, m);
        int v = 0;
        if (e.d == 1) v = id(e.i + 1, e.j, m);
        else v = id(e.i, e.j + 1, m);

        if (!dsu.Check(u, v)) {
            dsu.Unite(u, v);
            added.push_back(e);
            total_cost += e.d;
        }
    }

    std::cout << added.size() << " " << total_cost << "\n";
    for (const auto& e : added) {
        std::cout << e.i << " " << e.j << " " << e.d << "\n";
    }
}
