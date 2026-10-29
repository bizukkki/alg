#include<iostream>
#include <vector>

void dfs(std::vector<std::string> &lab, int x, int y, std::vector<std::pair<int, int>> &moves, 
         std::vector<std::vector<bool>> &v) {
    v[x][y] = true;
    for (auto move : moves) {
        int xm = x + move.first;
        int ym = y + move.second;
        if (lab[xm][ym] == '.' && !v[xm][ym]) dfs(lab, xm, ym, moves, v);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> lab(n);
    for (int i = 0; i < n; ++i) {
            std::string str;
            std::cin >> str;
            lab[i] = str;
    }
    std::vector<std::vector<bool>> visited(n, std::vector<bool> (n, false));
    int x, y;
    std::cin >> x >> y;
    std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    dfs(lab, x - 1, y - 1, moves, visited);
    int count_sq = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j){
            if (visited[i][j]) ++count_sq;
        }
    }
    std::cout << count_sq;
}