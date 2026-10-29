#include <iostream>
#include <vector>
#include <deque>

struct State {
    int x, y;
};

int main() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::vector<char>> g(h, std::vector<char>(w));
    for (int i = 0; i < h; i++) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < w; j++) {
            g[i][j] = s[j];
        }
    }
    int sx, sy, tx, ty;
    std::cin >> sx >> sy >> tx >> ty;
    sx--; 
    sy--;
    tx--;
    ty--;
    std::vector<std::pair<int,int>> moves = {{1,0}, {-1,0}, {0,1}, {0,-1},{1,1}, {1,-1}, {-1,1}, {-1,-1}};
    int inf = 1e9;
    std::vector<std::vector<int>> dist(h, std::vector<int>(w, inf));
    std::deque<State> dq;
    dist[sx][sy] = 1;
    dq.push_back({sx, sy});
    while (!dq.empty()) {
        State cur = dq.front();
        dq.pop_front();
        int x = cur.x;
        int y = cur.y;
        int cost = dist[x][y];
        for (auto [dx, dy] : moves) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
            if (g[nx][ny] == 'X') continue;
            if (dist[nx][ny] > cost) {
                dist[nx][ny] = cost;
                dq.push_front({nx, ny});
            }
        }

        // 1-cost "перенастройка направления"
        // (реализуется неявно через возможность входа с любой стороны)
    }

    std::cout << (dist[tx][ty] == inf ? -1 : dist[tx][ty]) << "\n";
}