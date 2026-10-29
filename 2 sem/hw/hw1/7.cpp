#include<iostream>
#include <vector>

void dfs(std::vector<std::vector<int>> &g, int now, int parent, std::vector<int> &colors, std::vector<int> &deep, int& longest) {
    colors[now] = 1;
    for (auto i : g[now]) {
        if (colors[i] == 0) {
            dfs(g, i, now, colors, deep, longest);
        }
    }
    colors[now] = 3;
    if ((g[now].size() == 2 && now != 1) || (now == 1 && g[now].size() == 1)) {
        for (auto i : g[now]) {
            if (i != parent){
                deep[now] = 1 + deep[i];
            }
            longest = std::max(longest, deep[now]);
        }
    } else if (g[now].size() >= 3 || now == 1) {
        int m1 = 0;
        int m2 = 0;
        for (auto i : g[now]) {
            if (i != parent){
                if (deep[i] >= m1){
                    m2 = m1;
                    m1 = deep[i];
                } else if (deep[i] >= m2) m2 = deep[i];
            }
        }
        deep[now] = 1 + m1;
        longest = std::max(longest, m1 + m2 + 2);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        graph[v2].push_back(v1);
        graph[v1].push_back(v2);
    }
    std::vector<int> colors(n + 1, false);
    std::vector<int> deep(n + 1, 0);
    int longest = 0;
    dfs(graph, 1, 0, colors, deep, longest);
    std::cout << longest << "\n";
    
}