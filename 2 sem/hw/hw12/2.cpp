#include <iostream>

long long gcd(long long a, long long b) {
    while (b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    long long a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b);
}