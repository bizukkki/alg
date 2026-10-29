#include<iostream>
#include <vector>
void dfs(std::vector<std::vector<int>> &g, int now, int parent, std::vector<int> &colors, std::vector<int> &count_v) {
    colors[now] = 1;
    for (auto i : g[now]) {
        if (colors[i] == 0) {
            dfs(g, i, now, colors, count_v);
        }
    }
    colors[now] = 3;
    for (auto i : g[now]) {
        if (i != parent){
            count_v[now] += count_v[i];
        }
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
    std::vector<int> count_vertex(n + 1, 1);
    dfs(graph, 1, 0, colors, count_vertex);
    for (int i = 1; i < n + 1; ++i) std::cout << count_vertex[i] << " ";
}