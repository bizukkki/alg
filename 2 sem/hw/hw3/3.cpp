#include <iostream>
#include <vector>
#include <queue>

struct Point {
    int z;
    int x;
    int y;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<std::vector<char>>> g(n, std::vector<std::vector<char>>(n, std::vector<char>(n)));
    std::vector<std::vector<std::vector<int>>> dist(n, std::vector<std::vector<int>>(n, std::vector<int>(n, -1)));
    int sx = -1, sy = -1, sz = -1;
    for (int z = 0; z < n; ++z) {
        for (int y = 0; y < n; ++y) {
            std::string s;
            std::cin >> s;
            for (int x = 0; x < n; ++x) {
                g[z][y][x] = s[x];
                if (g[z][y][x] == 'S') {
                    sz = z;
                    sy = y;
                    sx = x;
                    g[z][y][x] = '.';
                }
            }
        }
    }

    std::queue<Point> q;
    q.push({sz, sx, sy});
    dist[sz][sy][sx] = 0;
    std::vector<Point> moves = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
    while (!q.empty()) {
        Point cur = q.front();
        q.pop();
        if (cur.z == 0) {
            std::cout << dist[cur.z][cur.y][cur.x];
            return 0;
        }
        for (auto mv : moves) {
            int zn = cur.z + mv.z;
            int xn = cur.x + mv.x;
            int yn = cur.y + mv.y;
            if (zn >= 0 && zn < n &&
                yn >= 0 && yn < n &&
                xn >= 0 && xn < n) {
                if (g[zn][yn][xn] != '#' && dist[zn][yn][xn] == -1) {
                    dist[zn][yn][xn] = dist[cur.z][cur.y][cur.x] + 1;
                    q.push({zn, xn, yn});
                }
            }
        }
    }
}