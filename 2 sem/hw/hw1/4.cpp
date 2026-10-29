#include<iostream>
#include <vector>

bool findCycle(std::vector<std::vector<int>> &g, int now, int parent_v, std::vector<int> &colors, std::vector<int>& parents,
               std::vector<int>& cycle) {
    colors[now] = 1;
    for (int i : g[now]) {
        if (i == parent_v) {
            continue;
        }
        if (colors[i] == 0) {
            parents[i] = now;
            bool flag = findCycle(g, i, now, colors, parents, cycle);
            if (flag) {
                return true;
            }
        } else if (colors[i] == 1) {
            cycle.push_back(i);
            int cur = now;
            while (cur != i) {
                cycle.push_back(cur);
                cur = parents[cur];
            }
            return true;
        }
    }
    colors[now] = 2;
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            int x;
            std::cin >> x;
            if (x) {
                graph[i].push_back(j);
            }
        }
    }
    std::vector<int> colors(n + 1, 0);
    std::vector<int> parents(n + 1, -1);
    std::vector<int> cycle;
    bool has_cycle = false;

    for (int i = 1; i < n + 1; ++i) {
        if (colors[i] == 0) {
            has_cycle = findCycle(graph, i, 0, colors, parents, cycle);
            if (has_cycle) break;
        }
    }
    if (has_cycle) {
        std::cout << "YES" << std::endl;
        std::cout << cycle.size() << std::endl;
        for (auto v : cycle) {
            std::cout << v << " ";
        }
    } else {
        std::cout << "NO";
    }

    return 0;

}
