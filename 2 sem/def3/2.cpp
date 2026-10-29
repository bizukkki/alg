#include <iostream>

long long gcd(long long a, long long b) {
    while (b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    int a, b, c, d;
    int m, n;
    std::cin >> a >> b >> c >> d;
    int gcd_b_d = gcd(b, d);
    int nok_b_d = b / gcd_b_d * d;
    int new_b = nok_b_d / b;
    int new_d = nok_b_d / d; 
    //std:: cout << gcd_b_d <<" " << nok_b_d << " " << new_b << " " << new_d << "\n";
    n = nok_b_d;
    m = new_b * a + new_d * c;
    int gcd_m_n = gcd(m, n);
    //std::cout << gcd_m_n << "\n";
    m/=gcd_m_n;
    n/=gcd_m_n;
    std::cout << m << " " << n;
}