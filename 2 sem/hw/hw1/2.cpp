#include<iostream>
#include <vector>

void dfs(int now, std::vector<std::vector<int>> &g, std::vector<int> &v, std::vector<int> &comp) {
    v[now] = true;
    comp.push_back(now);
    for (int i : g[now]) {
        if (!v[i]) dfs(i, g, v, comp);
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
    std::vector<int> visited(n + 1, 0);
    std::vector<std::vector<int>> components;
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]){
            std::vector<int> comp;
            dfs(i, graf, visited, comp);
            components.push_back(comp);
        }
    }
    std::cout << components.size() << std::endl;
    for (std::vector<int> i : components) {
        std::cout<< i.size() << std::endl;
        for (int j : i) std::cout << j << " ";
        std::cout << std::endl;
    }
}
