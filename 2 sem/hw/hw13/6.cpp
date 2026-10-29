#include <iostream>
#include <vector>

int main() {
    int n;
    long long k;
    std::cin >> n >> k;
    std::vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    std::vector<int> used(n+1, false);
    for (int pos = 0; pos < n; pos++) {
        long long base = fact[n - pos - 1];
        int prev = 0;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                prev++;
            }
        }
        for (int i = n; i >= 1; i--) {
            if (!used[i]) {
                prev--;
                if (prev * base < k) {
                    std::cout << i << " ";
                    k -= prev * base;
                    used[i] = true;
                    break;
                }
            }
        }
    }
}