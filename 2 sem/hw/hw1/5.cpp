#include<iostream>
#include <vector>
void dfs(std::vector<std::vector<int>> &g, int now, std::vector<bool> &v) {
    v[now] = true;
    for (int i : g[now]) {
        if (!v[i]) dfs(g, i, v);
    }
}

int main() {
    int m, n;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        graph[v2].push_back(v1);
    }
    std::vector<bool> visited(n + 1, false);
    dfs(graph, 1, visited);
    for (int i = 1; i < n + 1; ++i) {
        if (visited[i]) std::cout << i << " ";
    }
}