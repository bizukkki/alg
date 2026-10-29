#include <iostream>
#include <vector>

struct Point {
    long long x;
    long long y;
    bool important = true;
    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points;
    for (int i = 0; i < n; ++i) {
        long long x;
        long long y;
        std::cin >> x >> y;
        x = std::abs(x);
        y = std::abs(y);
        points.push_back({x, y, true});
    }
    std::sort(points.begin(), points.end());
    std::vector<Point> p;
    for (int i = n - 1; i >= 0; --i) {
        if (!points[i].important) {
            continue;
        }
        p.push_back(points[i]);
        for (int j = i - 1; j >= 0; --j) {
            if (points[j].y <= points[i].y) {
                points[j].important = false;
            }
        }
    }
    std::reverse(p.begin(), p.end());
    int m = p.size();
    long long inf = 1e18;
    std::vector<long long> dp(m + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = std::min(dp[i], dp[j - 1] + p[i - 1].x * p[j - 1].y);
        }
    }
    std::cout << dp[m] * 4;
}