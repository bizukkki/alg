#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> lines(m);
    std::vector<std::vector<int>> station_to_lines(n + 1);
    for (int i = 0; i < m; ++i) {
        int p;
        std::cin >> p;
        for (int j = 0; j < p; ++j) {
            int v;
            std::cin >> v;
            lines[i].push_back(v);
            station_to_lines[v].push_back(i);
        }
    }
    int a, b;
    std::cin >> a >> b;

    std::vector<std::vector<bool>> adj(m, std::vector<bool>(m, false));
    for (int s = 1; s <= n; ++s) {
        std::vector<int> lst = station_to_lines[s];
        for (size_t i = 0; i < lst.size(); ++i) {
            for (size_t j = i + 1; j < lst.size(); ++j) {
                int line1 = lst[i];
                int line2 = lst[j];
                adj[line1][line2] = true;
                adj[line2][line1] = true;
            }
        }
    }
    std::vector<int> dist(m, -1);
    std::queue<int> q;
    for (int line : station_to_lines[a]) {
        dist[line] = 0;
        q.push(line);
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int st : lines[v]) {
            if (st == b) {
                std::cout << dist[v];
                return 0;
            }
        }
        for (int to = 0; to < m; ++to) {
            if (adj[v][to] && dist[to] == -1) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }

    std::cout << -1;
    return 0;
}