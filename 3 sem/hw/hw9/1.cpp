#include <iostream>

int main() {
    double a, b, c;
    double x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    a = y1 - y2;
    b = x2 - x1;
    c = x1 * y2 - x2 * y1;
    std::cout << a << " " << b << " " << c;
}