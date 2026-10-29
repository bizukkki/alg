#include <iostream>
#include <vector>
#include <cmath>
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

double len(Vector a) {
    return a.x * a.x + a.y * a.y;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Vector> points(n);
    int min_y = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
        if (points[i].y <  points[min_y].y 
            || (points[i].y == points[min_y].y && points[i].x <  points[min_y].x)) {
            min_y = i;
        }
    }
    std::swap(points[0], points[min_y]);
    Vector p = points[0];
    std::sort(points.begin() + 1, points.end(), [&](const Vector& a, const Vector& b) {
        Vector pa = a - p;
        Vector pb = b - p;
        double prod = vec_prod(pa, pb);
        if (prod == 0) return len(pa) < len(pb);
        return prod > 0;
    });
    std::vector<Vector> stack;
    stack.push_back(points[0]);
    stack.push_back(points[1]);
    for(int i = 2; i < n; i++) {
        while (stack.size() >= 2) {
            Vector b = stack[stack.size() - 1];
            Vector a = stack[stack.size() - 2];
            Vector c = points[i];
            Vector ab = b - a;
            Vector ac = c - a;
            double prod = vec_prod(ac, ab);
            if (prod >= 0) stack.pop_back();
            else break;
        }
        stack.push_back(points[i]);
    }
    double per = 0;
    double s = 0;
    int m = stack.size();
    for (int i = 0; i < m; i++) {
        Vector cur = stack[i];
        Vector next = stack[(i+1)%m];
        Vector side  = next - cur;
        per += std::sqrt(len(side));
        s += vec_prod(cur, next);
    }
    s /= 2.0;
    if (s < 0) s = -s;
    std::cout << std::fixed << std::setprecision(10) << per << "\n" << s;
}