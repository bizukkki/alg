#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    int k = int(std::log2(double(n))) + 1;
    std::vector<std::vector<int>> sp(k, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        std::cin>>sp[0][i];
    }
    for (int i = 1; i < k; i++) {
        for (int j = 0; j + (1 << i) - 1 <= n - 1; j++) {
            sp[i][j] = std::min(sp[i-1][j], sp[i-1][j + (1 << (i - 1))]);
        }
    }
    int q;
    std::cin>>q;
    long long answ = 0;
    int l, r;
    for (int i = 0; i < q; i++) {
        std::cin >> l >> r;
        int p = int(std::log2(double(r - l + 1)));
        answ+= std::min(sp[p][l], sp[p][r - (1 << p) + 1]
        );
    }
    std::cout << answ;
}