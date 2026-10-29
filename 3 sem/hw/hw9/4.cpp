#include <iostream>

struct Vector {
    double x;
    double y;
    Vector(double x1 = 0, double y1 = 0) : x(x1), y(y1) {};
    Vector operator-() {
        return Vector(-x, -y);
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
    double ax, ay, bx, by, cx, cy, dx, dy;
    std::cin >> ax >> ay >> bx >> by >> cx >>  cy >> dx >> dy;
    Vector ab(bx-ax, by - ay);
    Vector ac(cx -ax, cy - ay);
    Vector ad(dx -ax, dy - ay);
    if (vec_prod(ab, ac) * vec_prod(ab, ad) > 0) {
        std::cout << "NO";
        return 0;
    }
    Vector cd(dx -cx, dy - cy);
    Vector cb(bx -cx, by -cy);
    if (vec_prod(cd, cb) * vec_prod(cd, -ac) > 0) std::cout << "NO";
    else {
        if (!projection(ax, bx, cx, dx) || !projection(ay, by, cy, dy)){
            std::cout << "NO";
        }
        else std::cout << "YES";
    }
}