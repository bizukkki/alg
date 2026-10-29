#include <iostream>
#include <vector>

void rec(std::vector<int>& vec, int n, int sum, int pos, int prev) {
    if (sum == n) {
        for (int i = 0; i < pos; i++) std::cout << vec[i] << " ";
        std::cout << '\n';
        return;
    }
    for (int i = 1; i <= std::min(prev, n - sum); i++) {
        vec[pos] = i;
        rec(vec, n, sum + i, pos + 1, i);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    rec(vec, n, 0, 0, n);
}