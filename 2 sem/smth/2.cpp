#include <iostream>
#include <vector>
#include <queue>

struct Square {
    int x;
    int y;
    int weight;
    bool operator>(const Square& other) const{
        return weight > other.weight;
    }
};

int main() {
    int n, m, xs, ys, xf, yf;
    std::cin >> n >> m >> xs >> ys >> xf >> yf;
    std::vector<std::vector<Square>> g;
    std::vector<std::vector<char>> field(n+1, std::vector<char> (m+1));
    for (int x = 1; x < n+1; x++) {
        for (int y = 1 ; y < m +1; y++){
            char c;
            std::cin >> c;
            field[x][y] = c;
        }
    }
    int inf = 1e9;
    std::vector<std::vector<int>> dist(n+1, std::vector<int>(m+1, inf));
    dist[xs][ys] = 0;
    std::priority_queue<Square, std::vector<Square>, std::greater<Square>> min_heap;
    min_heap.push({xs, ys, 0});
    std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while(!min_heap.empty()) {
        auto now = min_heap.top();
        min_heap.pop();
        int x = now.x;
        int y = now.y;
        int w = now.weight;
        if (w > dist[x][y]) continue;
        for (auto move : moves) {
            int nx = x + move.first;
            int ny = y + move.second;
            if (nx <= n && nx > 0 && ny <= m && ny > 0) {
                if (field[nx][ny] == '.') {
                    if (dist[nx][ny] > w + 1){
                        dist[nx][ny] = w + 1;
                        min_heap.push({nx, ny, dist[nx][ny]});
                    }
                } else if (field[nx][ny] == 'W') {
                    if (dist[nx][ny] > w + 2){
                        dist[nx][ny] = w + 2;
                        min_heap.push({nx, ny, dist[nx][ny]});
                    }
                }
            }
        }
    }
    for (int x = 1; x < n+1; x++) {
        for (int y = 1 ; y < m +1; y++){
            std::cout << dist[x][y] << " ";
        }
        std::cout << "\n";
    }
    if (dist[xf][yf] != inf) std::cout << dist[xf][yf];
    else std::cout << -1;
}