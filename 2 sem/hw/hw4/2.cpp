#include <iostream>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    std::vector<std::vector<Edge>> g(n+1);
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int w;
            std::cin >> w;
            if (w!=-1 && w != 0) {
                g[i].push_back({i, j, w});
            }
        }
    }
    std::vector<bool> used(n+1, false);
    int inf = 1000000000;
    std::vector<int> dist(n+1, inf);
    std::vector<int> prev(n+1, -1);
    prev[s] = 0;
    dist[s] = 0;
    for(int i = 1; i < n + 1; ++i) {
        int v = -1;
        for (int u = 1; u < n + 1; u++) {
            if ((v == -1 || dist[u] < dist[v]) && !used[u]){
                v = u;

            }
        }
        if (v == -1) break;
        used[v] = true;
        for (auto ch : g[v]) {
            if (dist[ch.to] > dist[v] + ch.weight) {
                dist[ch.to] = dist[v] + ch.weight;
                prev[ch.to] = v;
            }
        }
    }
    if (dist[f] != inf) {
        std::vector<int> answer;
        answer.push_back(f);
        int p = prev[f];
        while (p != 0) {
            answer.push_back(p);
            p = prev[p];
        }
        std::reverse(answer.begin(), answer.end());
        for (auto i : answer) std::cout << i << " ";
    }
    else std::cout << -1;
}