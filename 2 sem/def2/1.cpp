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
    long long cost;
    long long first;
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};
struct Point {
    long long x;
    long long y;
    long long cost;
};
int id(int x, int y) {
    if (x > 0) x = 1001 + x;
    else x = 1000 + x + 1;
    if (y > 0) y = 1001 + y;
    else y = 1000 + y + 1;
    return x + (y - 1) * 2001;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Edge> edges;
    std::vector<Point> points;
    long long x1, y1, x2, y2;
    long long cost1, cost2;
    Edge min_fisrt;
    bool flag = false;
    for (int i = 1; i < n + 1; ++i) {
        std::cin >> x1 >> y1 >> cost1;
        for (int j = 0; j < i - 1; j++) {
            x2 = points[j].x;
            y2 = points[j].y;
            cost2 = points[j].cost;
            long long dist = (x1 - x2)*(x1-x2) + (y1-y2)*(y1-y2);
            int id1 = id(x1, y1);
            int id2 = id(x2, y2);
            Edge e1, e2;
            e1.from = id1;
            e1.to = id2;
            e1.cost = std::min(dist, cost2);
            e1.first = cost1;
            edges.push_back(e1);
            e2.from = id2;
            e2.to = id1;
            e2.first = cost2;
            e2.cost = std::min(dist, cost1);
            edges.push_back(e2);
            if (!flag) {
                if (cost1 < cost2) {
                    min_fisrt = {id1, id2, cost1 + std::min(dist, cost2), cost1};
                } else {
                    min_fisrt = {id2, id1, cost2 + std::min(dist, cost1), cost2};
                }
            } else {
                if (cost1 + std::min(dist, cost2) < min_fisrt.cost) {
                    min_fisrt = {id1, id2, cost1 + std::min(dist, cost2) , cost1};
                }
                if (cost2 + std::min(dist, cost1)< min_fisrt.cost) {
                    min_fisrt = {id2, id1, cost2 + std::min(dist, cost1), cost2};
                }
            }
        }
        points.push_back({x1, y1, cost1});
    }
    std::sort(edges.begin(), edges.end());
    DSU dsu(3001 * 2001);
    long long answer = 0;
    dsu.Unite(min_fisrt.from, min_fisrt.to);
    answer += min_fisrt.cost;
    for (const auto& e : edges) {
        if (!dsu.Check(e.from, e.to)) {
            dsu.Unite(e.from, e.to);
            answer += e.cost;
        }
    }
    std::cout << answer;
}