#include<iostream>
#include <vector>

void dfs(int now, std::vector<std::vector<int>> &g, std::vector<int> &v, int color, bool &flag) {
    v[now] = color;
    for (int i : g[now]) {
        if (!v[i]) {
            dfs(i, g, v, 3 - color, flag);
        } else if (color == v[i]) {
            flag = false;
        }
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
    bool flag = true;
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i]){
            dfs(i, graf, visited, 1, flag);
        }
    }
    if (!flag){
        std::cout<< "0";
    } else {
        for (int i = 1; i < n +1; i++) {
            if (visited[i] == 1) std::cout << i << " ";
        }
        std::cout << "\n";
        for (int i = 1; i < n +1; i++) {
            if (visited[i] == 2) std::cout << i << " ";
        }
    }
}