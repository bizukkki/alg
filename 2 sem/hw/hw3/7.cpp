#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> g[i][j];
        }
    }
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    std::queue<std::pair<int,int>> q;
    q.push({0, 0});
    dist[0][0] = 0;
    std::vector<std::pair<int,int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        int x = now.first;
        int y = now.second;
        for (auto move : moves) {
            int xn = x;
            int yn = y;
            while (true) {
                int x_to = xn + move.first;
                int y_to = yn + move.second;

                if (x_to < 0 || y_to < 0 || x_to >= n || y_to >= m) break;
                if (g[x_to][y_to] == 1) break;

                xn = x_to;
                yn = y_to;

                if (g[xn][yn] == 2) {
                    std::cout << dist[x][y] + 1;
                    return 0;
                }
            }
            if (dist[xn][yn] == -1) {
                dist[xn][yn] = dist[x][y] + 1;
                q.push({xn, yn});
            }
        }
    }
    return 0;
}