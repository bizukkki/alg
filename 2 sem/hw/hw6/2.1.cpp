#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
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
        if (v == parent_[v]) {
            return v;
        }
        return parent_[v] = Leader(parent_[v]);
    }
    void Unite(int a, int b) {
        a = Leader(a);
        b = Leader(b);
        if (a == b) {
            return;
        }
        if (weight_[a] < weight_[b]) {
            std::swap(a, b);
        }
        parent_[b] = a;
        weight_[a] += weight_[b];
    }

    bool Check(int a, int b) {
        a = Leader(a);
        b = Leader(b);
        return a == b;
    }
};

struct Point {
    int x;
    int y;
};

struct Edge {
    int from;
    int to;
    double weight;
    bool operator < (const Edge& other) const {
        return weight < other.weight;
    }
};

double Distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> vertexs(n + 1);
    for (int i = 1; i < n + 1; i++) {
        std::cin >> vertexs[i].x >> vertexs[i].y;
    }
    std::vector<std::vector<bool>> is_edge(n + 1, std::vector<bool>(n + 1, false));
    std::vector<Edge> edges;
    int m;
    std::cin >> m;
    for (int i = 1; i < m + 1; i++) {
        int v1, v2;
        std::cin >> v1 >> v2;
        is_edge[v1][v2] = true;
        is_edge[v2][v1] = true;
        edges.push_back({v1, v2, 0.0});
    }
    for (int i = 1; i < n + 1; i++) {
        Point p = vertexs[i];
        for (int j = 1; j < i; j++) {
            if (!is_edge[i][j]) {
                Point p1 = vertexs[j];
                double dist = pow((p.x - p1.x), 2) + pow((p.y - p1.y), 2);
                edges.push_back({i, j, dist});
            }
        }
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(n);
    double answer = 0.0;
    int count_edges = 0;
    for (const auto& e : edges) {
        if (!dsu.Check(e.from, e.to)) {
            dsu.Unite(e.from, e.to);
            answer += e.weight;
            count_edges++;
            if (count_edges == n - 1) {
                break;
            }
        }
    }
    std::cout << std::fixed << std::setprecision(6) << answer;
}