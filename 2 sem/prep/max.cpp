#include <iostream>

int main() 
{
    int p_max1 = -1;
    int p_max2 = 0;
    int n_min1 = 1;
    int n_min2 = 0;
    int a;
    while (std::cin >> a) {
        if (a > 0) {
            if (a >= p_max1) {
                p_max2 = p_max1;
                p_max1 = a;
            } else if (a >= p_max2) {
                p_max2 = a;
            }
        } else {
            if (a <= n_min1) {
                n_min2 = n_min1;
                n_min1 = a;
            } else if (a <= n_min2) {
                n_min2 = a;
            }
        }
    }
    if (p_max1 * p_max2 > n_min1 * n_min2) {
        std::cout <<p_max2  << " " << p_max1;
    } else {
        std::cout << n_min1 << " " << n_min2;
    }
	return 0;
}