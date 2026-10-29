#include <iostream>
#include <vector>
#include <set>
#include <cmath>

struct Point {
    int64_t x, y;
};

struct Line {
    int a, b, c;
};

int main() {
    int n, m, r;
    std::cin >> n >> m >> r;
    std::vector<Point> candl(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> candl[i].x >> candl[i].y;
    }
    std::vector<Line> lines(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> lines[i].a >> lines[i].b >> lines[i].c;
    }
    std::set<std::vector<int>> pieces;
    for (int i = 0; i < n; ++i) {
        std::vector<int> position;
        for (int j = 0; j < m; ++j) {
            int val = lines[j].a * candl[i].x + lines[j].b * candl[i].y + lines[j].c;
            if (val > 0) {
                position.push_back(1);
            } else {
                position.push_back(-1);
            }
        }
        pieces.insert(position);
    }
    if (pieces.size() < n)std::cout << "YES";
    else std::cout << "NO";
}
