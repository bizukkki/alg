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
    int n;
    std::cin >> n;
    std::vector<Vector> p(n);
    std::cin >> p[0].x >> p[0].y;
    double s = 0;
    for (int i = 1; i < n; i++) {
        std::cin >> p[i].x >> p[i].y;
        Vector cur = p[i];
        Vector prev = p[i-1];
        s += vec_prod(prev, cur);
    }
    s += vec_prod(p[n-1], p[0]);
    s /= 2.0;
    if (s < 0) s = -s;
    std::cout << std::fixed << std::setprecision(5) << s;
}