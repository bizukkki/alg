#include <iostream>
#include <vector>
#include <iomanip>

struct Vector {
    double x;
    double y;
    Vector(double x1 = 0, double y1 = 0) : x(x1), y(y1) {};
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator-() const {
        return Vector(-x, -y);
    }
    Vector operator*(double k) const {
        return Vector(x * k, y * k);
    }
};

double vec_prod(Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

double scal_prod(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool projection(double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

int main() {
    Vector a, b, c;
    std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    Vector ab = b - a;
    Vector ac = c - a;
    double s = vec_prod(ab, ac);
    s /= 2.0;
    if (s < 0) s = -s;
    std::cout << s;
}