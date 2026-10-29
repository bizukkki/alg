#include<iostream>
#include <vector>

void dfs(std::vector<std::vector<int>> &g, int now, std::vector<int> &colors, std::vector<int> &tsort, bool &flag) {
    colors[now] = 1;
    for (auto i : g[now]) {
        if (colors[i] == 0) {
            dfs(g, i, colors, tsort, flag);
        } else if (colors[i] == 1) flag = false;
    }
    colors[now] = 2;
    tsort.push_back(now);
}

int main() {
    int m, n;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graf(n + 1);

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        graf[v1].push_back(v2);
    }
    std::vector<int> topol_sort;
    std::vector<int> color(n+1, 0);
    bool flag = true;
    for (int i = 1; i < n + 1; ++i){
        if (color[i] == 0) {
            dfs(graf, i, color, topol_sort, flag);
        } 
    }
    std::reverse(topol_sort.begin(), topol_sort.end());
    if (flag) {
        for (auto v : topol_sort) {
            std::cout << v << " ";
        }

    } else std::cout << -1;
}
