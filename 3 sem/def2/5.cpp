#include <iostream>
#include <vector>
#include <iomanip>

struct Point {
    double x;
    double y;
    Point(double x1 = 0, double y1 = 0) : x(x1), y(y1) {};
    
};
double ABS(double a) {
    if (a < 0) return -a;
    return a;
}
int main() {
    double x1, x2, x3, x4, y1, y2, y3, y4; 
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    double abx = ABS(x1 - x2);
    double aby = ABS(y1 - y2);
    double cdx = ABS(x3 - x4);
    double cdy = ABS(y3 - y4);

    double abxmin = std::min(x1, x2);
    double abymin = std::min(y1, y2);
    Point a(abxmin, abymin);
    Point b(abxmin + abx, abymin + aby);

    double cdxmin = std::min(x3, x4);
    double cdymin = std::min(y3, y4);
    Point c(cdxmin, cdymin);
    Point d(cdxmin + cdx, cdymin + cdy);

    if (c.x < a.x) {
        std::swap(a, c);
        std::swap(b, d);
    }

    //std::cout << a.x << " " << a.y << "\n";
    //std::cout << b.x << " " << b.y << "\n";
    //std::cout << c.x << " " << c.y << "\n";
    //std::cout << d.x << " " << d.y << "\n";

    if (b.x < c.x || b.y < c.y || d.y < a.y) {
        std::cout << "NO";
        return 0;
    }
    if (a.x  < c. x && d.x < b.x && a.y < c.y && d.y < b.y) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES";
}