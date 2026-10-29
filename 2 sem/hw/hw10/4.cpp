#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    int k = int(std::log2(double(n))) + 1;
    std::vector<std::vector<long long>> sp(k, std::vector<long long>(n));
    std::cin >> sp[0][0];
    for (int i = 1; i < n; i++) {
        sp[0][i] = (23 * sp[0][i-1] + 21563) % 16714589;

    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j + (1 << i) - 1 <= n - 1; j++) {
            sp[i][j] = std::min(sp[i-1][j], sp[i-1][j + (1 << (i - 1))]);
        }
    }
    long long answ = 0;
    int u, v;
    std::cin>> u >> v;
    int l = u - 1;
    int r = v - 1;
    int p = int(std::log2(double(r - l + 1)));
    answ = std::min(sp[p][l], sp[p][r - (1 << p) + 1]);
    for (int i = 1; i < m; i++) {
        u = ((17 * u + 751 + answ + 2 * i) % n) + 1;
        v = ((13 * v + 593 + answ + 5*i)%n) + 1;
        l = std::min(u, v) - 1;
        r = std::max(u, v) - 1;
        p = int(std::log2(double(r - l + 1)));
        answ = std::min(sp[p][l], sp[p][r - (1 << p) + 1]);
    }
    std::cout << u << " " << v << " " << answ;
}