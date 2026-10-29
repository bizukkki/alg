#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    long long x, y;
};

double get_dist(Point& a, Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<Point> pts(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> pts[i].x >> pts[i].y;
    }
    std::vector<std::vector<double>> d(n + 1, std::vector<double>(n + 1, 0.0));
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double dist = get_dist(pts[i], pts[j]);
            d[i][j] = dist;
            d[j][i] = dist;
        }
    }
    std::vector<int> tour;
    std::vector<bool> visited(n + 1, false);
    int cur = 1;
    tour.push_back(cur);
    visited[cur] = true;
    for (int step = 1; step < n; ++step) {
        int next_v = -1;
        double min_d = 1e18;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && d[cur][i] < min_d) {
                min_d = d[cur][i];
                next_v = i;
            }
        }
        cur = next_v;
        tour.push_back(cur);
        visited[cur] = true;
    }
    tour.push_back(1);
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 2; j < n; ++j) {
                double old_dist = d[tour[i]][tour[i+1]] + d[tour[j]][tour[j+1]];
                double new_dist = d[tour[i]][tour[j]] + d[tour[i+1]][tour[j+1]];
                if (new_dist < old_dist - 1e-9) {
                    int left = i + 1;
                    int right = j;
                    while (left < right) {
                        std::swap(tour[left], tour[right]);
                        left++;
                        right--;
                    }
                    improved = true;
                }
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        std::cout << tour[i] << " ";
    }
}
