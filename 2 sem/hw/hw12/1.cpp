#include <iostream>

long long binpow(long long x, long long n, long long p) {
    if (n == 0) return 1 % p;
    if (n % 2 == 1) return (binpow(x, n - 1, p) * x ) % p;
    long long y = binpow(x, n / 2, p);
    return (y * y) % p;
}

int main() {
    long long x, n, p;
    std::cin >> x >> n >> p;
    std::cout << binpow(x, n, p);
}