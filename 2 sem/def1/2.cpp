#include<iostream>
#include <vector>

struct Edge {
    int from;
    int to;
};

int main() {
    int m, n;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        edges.push_back({v1, v2});
    }
    std::vector<int> top_sort (n+1, 0);
    for (int i = 1; i < n + 1; i++) {
        int v;
        std::cin >> v;
        top_sort[v] = i;
    }
    for (auto e : edges){
        if (top_sort[e.from] > top_sort[e.to]) {
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
}