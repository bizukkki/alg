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
    std::vector<Vector> points(n);
    Vector p;
    std::cin >> p.x >> p.y;
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }
    bool cross = false;
    for (int i = 0; i < n; i++) {
        Vector a = points[i];
        Vector b = points[(i+1) % n];
        Vector ab = b - a;
        Vector ap = p - a;
        double prod = vec_prod(ab, ap);

        Vector bp = p - b;
        Vector ba = a - b;
        if (prod == 0 && scal_prod(ab, ap) >= 0 && scal_prod(bp, ba)>= 0) {
            std::cout << "YES";
            return 0;
        }
        if (a.y <= p.y && p.y < b.y) {
            if (prod > 0) {
                cross = !cross;
            }
        }
        else if (b.y <= p.y && p.y < a.y) {
            if (prod < 0) {
                cross = !cross;
            }
        }
    }
    if (cross) std::cout << "YES";
    else std::cout << "NO";
}