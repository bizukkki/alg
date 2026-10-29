#include <iostream>
#include <vector>
#include <queue>

int main() {  
    int n, m, s, t, q;
    std::cin>> n >> m >> s >> t >> q;
    int start_x = s - 1;
    int start_y = t - 1;
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    dist[start_x][start_y] = 0;
    std::queue<std::pair<int, int>> que;
    que.push({start_x, start_y});
    std::vector<std::pair<int, int>> moves = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    while (!que.empty()) {
        std::pair<int, int> now = que.front();
        que.pop();
        int x = now.first;
        int y = now.second;
        for (auto move : moves) {
            int xn = x + move.first;
            int yn = y + move.second;
            if (xn >= 0 && xn < n && yn >= 0 && yn < m) {
                if (dist[xn][yn] == -1) {
                    dist[xn][yn] = dist[x][y] + 1;
                    que.push({xn, yn});
                }
            }
        }
    }
    long long total = 0; 
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        x--; 
        y--;
        if (dist[x][y] == -1) {
            std::cout << -1 << std::endl;
            return 0;
        }
        total += dist[x][y];
    }
    std::cout << total << std::endl;
}