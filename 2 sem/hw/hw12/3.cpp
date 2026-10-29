#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    for (long long i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            std::cout << i << " ";
            n /= i;
        }
    }
    if (n > 1) {
        std::cout << n;
    }
}