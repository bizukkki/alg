#include <iostream>

long long gcd(long long a, long long b) {
    while (b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    long long x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << gcd(std::abs(x1-x2), std::abs(y1-y2)) + 1;
};


long long ABS(long long a) {
    if (a > 0) return a;
    return -a;
}