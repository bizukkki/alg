#include <iostream>

struct Vector {
    double x;
    double y;
    Vector(double x1, double y1) : x(x1), y(y1) {};
};

double vec_prod(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

double scal_prod(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int main() {
    double px, py, x1, y1, x2, y2;
    std::cin >> px >> py;
    std::cin >> x1 >> y1 >> x2 >> y2;
    Vector ab(x2 - x1, y2 - y1);
    Vector ap(px - x1, py - y1);
    if (vec_prod(ab, ap) == 0 && scal_prod(ab, ap) >= 0) std::cout << "YES";
    else std::cout << "NO";
}