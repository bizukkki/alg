#include <iostream>
#include <vector>
#include <deque>

struct State {
    int x, y, dir;
};

int main() {
    int h, w;
    std::cin >> h >> w;

    std::vector<std::vector<char>> g(h, std::vector<char>(w));
    std::string s;

    for (int i = 0; i < h; i++) {
        std::cin >> s;
        for (int j = 0; j < w; j++) {
            g[i][j] = s[j];
        }
    }

    int sx, sy, tx, ty;
    std::cin >> sx >> sy >> tx >> ty;

    sx--; sy--;
    tx--; ty--;

    std::vector<std::pair<int,int>> moves = {
        {1,0}, {-1,0}, {0,1}, {0,-1},
        {1,1}, {1,-1}, {-1,1}, {-1,-1}
    };

    const int INF = 1e9;

    std::vector<std::vector<std::vector<int>>> dist(
        h, std::vector<std::vector<int>>(w, std::vector<int>(8, INF))
    );

    std::deque<State> dq;

    for (int d = 0; d < 8; d++) {
        dist[sx][sy][d] = 1;
        dq.push_back({sx, sy, d});
    }

    auto inside = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < h && y < w;
    };

    while (!dq.empty()) {
        State cur = dq.front();
        dq.pop_front();

        int x = cur.x;
        int y = cur.y;
        int dir = cur.dir;
        int cost = dist[x][y][dir];

        // 🔥 ДВИЖЕНИЕ ДО УПОРА (0 cost)
        int nx = x;
        int ny = y;

        while (true) {
            int tx2 = nx + moves[dir].first;
            int ty2 = ny + moves[dir].second;

            if (!inside(tx2, ty2)) break;
            if (g[tx2][ty2] == 'X') break;

            nx = tx2;
            ny = ty2;

            if (dist[nx][ny][dir] > cost) {
                dist[nx][ny][dir] = cost;
                dq.push_front({nx, ny, dir});
            }
        }

        // 🔥 повороты (1 cost)
        for (int nd = 0; nd < 8; nd++) {
            if (nd == dir) continue;

            if (dist[x][y][nd] > cost + 1) {
                dist[x][y][nd] = cost + 1;
                dq.push_back({x, y, nd});
            }
        }
    }

    int ans = INF;
    for (int d = 0; d < 8; d++) {
        ans = std::min(ans, dist[tx][ty][d]);
    }

    std::cout << (ans == INF ? -1 : ans);
}