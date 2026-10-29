#include<iostream>
#include <vector>

void dfs(int now, std::vector<std::vector<int>> &g, std::vector<bool> &v) {
    v[now] = true;
    for (int i : g[now]) {
        if (!v[i]) dfs(i, g, v);
    }
}

int main() {
    int m, n;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graf(n + 1);

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        graf[v1].push_back(v2);
        graf[v2].push_back(v1);
    }
    std::vector<bool> visited(n + 1, false);
    dfs(1, graf, visited);
    std::vector<int> component;
    for (int i; i < n + 1; ++i) {
        if (visited[i]) component.push_back(i);
    }
    std::cout << component.size() << std::endl;
    for (int i : component) {
        std::cout<< i << " ";
    }
}
