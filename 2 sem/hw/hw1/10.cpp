#include <iostream>
#include <vector>

struct Component {
    int height;
    bool lower;
};

void dfs(std::vector<std::vector<int>>& f, std::vector<std::vector<int>>& comp,
        int row, int col, int id, int n, int m, std::vector<std::pair<int, int>> &moves) {
    comp[row][col] = id;
    for (auto move : moves) {
        int row_n = row + move.first;
        int col_n = col + move.second;
        if (row_n >= 0 && row_n < n && col_n >= 0 && col_n < m){
            if(comp[row_n][col_n] == -1 && f[row_n][col_n] == f[row][col]){
                dfs(f, comp, row_n, col_n, id, n, m, moves);
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> field(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> field[i][j];
        }
    }
    std::vector<std::vector<int>> comp(n, std::vector<int>(m, -1));
    std::vector<Component> components;
    std::vector<std::pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int comp_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (comp[i][j] == -1) {
                components.push_back({field[i][j], false});
                dfs(field, comp, i, j, comp_count, n, m, moves);
                comp_count++;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int id = comp[i][j];
            if (!components[id].lower) {
                for (auto move : moves) {
                    int row_n = i + move.first;
                    int col_n = j + move.second;
                    if (row_n >= 0 && row_n < n && col_n >= 0 && col_n < m) {
                        if (field[row_n][col_n] < field[i][j]) {
                            components[id].lower = true;
                        }
                    }
                }
            }
        }
    }
    int answer = 0;
    for (auto c : components) {
        if (!c.lower) {
            answer++;
        }
    }
    std::cout << answer;
}