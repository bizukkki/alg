#include <iostream>
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
    std::cout << std::fixed << std::setprecision(2);
    double ax, ay, bx, by, cx, cy, dx, dy;
    std::cin >> ax >> ay >> bx >> by >> cx >>  cy >> dx >> dy;
    Vector a(ax, ay), b(bx, by), c(cx, cy), d(dx, dy);
    Vector ab = b - a;
    Vector cd = d - c;
    Vector ac = c - a;
    Vector ad = d - a;
    if (vec_prod(ab, cd) == 0) {
        if (vec_prod(ab, ac) == 0) std:: cout << 2;
        else std::cout << 0;
        return 0;
    }
    double s1 = vec_prod(ab, ac);
    double s2 = vec_prod(ab, ad);
    double k = s1 / ( s1 - s2);
    Vector p = c + ( cd * k );
    std::cout << 1 << " " << p.x << " " << p.y;
}