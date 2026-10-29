#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    long long answ = -1e18;
    long long x;
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        cur+=x;
        answ = std::max(answ, cur);
        cur = std::max(cur, static_cast<long long>(0));
    }
    std::cout << answ;
}