#include <iostream>
#include <vector>

int main() {
    long long n, m;
    std::cin >> m >> n;
    std::vector<int> is_prime(n + 1, 1);
    bool flag = false;
    for(int k = 2; k <= n; k++) {
        if (is_prime[k]) {
            if (k >= m) {
                std::cout << k << "\n";
                flag = true;
            }
            int p = 2 * k;
            while (p <= n) {
                is_prime[p] = 0;
                p+=k;
            }
        }
    }
    if (!flag) std::cout << "Absent";
}