#include <iostream>
#include <vector>
#include <iomanip>

bool dfs(std::vector<std::vector<int>> &g, int now, std::vector<int> &colors, int c) {
    colors[now] = c;
    for (int i : g[now]) {
        if (!colors[i]) {
            if (!dfs(g, i, colors, 3 - c)) return false;
        } else if (c == colors[i]) return false;
    }
    return true;
}

bool check (std::vector<std::pair<int, int>> &towers, double limit,   std::vector<int> &colors, int n) {
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dx = towers[i].first - towers[j].first;
            double dy = towers[i].second - towers[j].second;
            double dist2 = dx * dx + dy * dy;
            if (dist2 < limit) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    std::fill(colors.begin(), colors.end(), 0);
    for (int i = 0; i < n; ++i) {
        if (colors[i] == 0) {
            if (!dfs(graph, i, colors, 1)) {
                return false;
            }
        }
    }
    return true;

}    
int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> towers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> towers[i].first >> towers[i].second;
    }
    std::vector<int> colors(n, 0);
    std::vector<int> answer(n, 1);
    double left = 0.0;
    double right = 20000.0; 
    while (right - left > 1e-7) {
        double mid = (left + right) / 2.0;
        double limit = 4.0 * mid * mid;
        if (check(towers, limit, colors, n)) {
            left = mid;
            answer = colors;
        } else {
            right = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(15) << left << std::endl;
    for (int color : answer) {
        std::cout << color << " ";
    }
}