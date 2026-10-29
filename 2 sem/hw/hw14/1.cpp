#include <iostream>
#include <vector>

void rec(std::vector<int>& perm, std::vector<std::vector<int>>& g, int n, int pos, long long sum, long long& answer, int min_edge) {
    if (sum + min_edge * (n - pos + 1) >= answer) {
        return;
}
    if (sum >= answer) {
        return;
    }
    if (pos == n - 1) {
        int last;
        if (n == 1) last = 1;
        else last = perm[n - 2];
        if (g[last][1] == 0) {
            return;
        }
        sum += g[last][1];
        if (sum < answer) answer = sum;
        return;
    }
    int last;
    if (pos == 0) last = 1;
    else last = perm[pos - 1];
    for (int i = pos; i < n - 1; i++) {
        std::swap(perm[pos], perm[i]);
        int now = perm[pos];
        if (g[last][now] != 0) {
            rec(perm, g, n, pos + 1, sum + g[last][now], answer, min_edge);
        }
        std::swap(perm[pos], perm[i]);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1));
    int min_edge = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int len;
            std::cin >> len;
            g[i][j] = len;
            if (len < min_edge && len !=0) min_edge = len;
        }
    }
    if (n == 1) {
        std::cout << 0;
        return 0;
    }
    std::vector<int> perm;
    for (int i = 2; i <= n; i++) {
        perm.push_back(i);
    }
    long long answer = 1e18;
    rec(perm, g, n, 0, 0, answer, min_edge);
    if (answer == 1e18) {
        std::cout << -1;
    } else {
        std::cout << answer;
    }
}