#include <iostream>
#include <iomanip>

int main() {
    double X, Y, x1, y1, x2, y2, x3, y3, x4, y4;
    std::cin >> X >> Y >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >>  x4 >> y4;
    //x' = ax + by + c
    //y' = dx + ey + f
    double a, b, c, d, e, f;
    c = x1;
    f = y1;
    a = (x2 - x1) / X;
    d = (y2 - y1) / X;
    b = (x4 - x1) / Y;
    e = (y4 - y1) / Y;
    //(1-a)x - by =c;
    //-dx + (1 -e) y = f
    double det = (1 - a) * (1 - e) - (-b) * (-d);
    double detx = c * (1 - e) - (-b) * f;
    double dety = (1 - a) * f - c * (-d);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << detx / det << " " << dety / det;
}