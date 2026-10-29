#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    int min_del = -1;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            min_del = i;
            break;
        }
    }
    if (min_del == -1) std::cout << 1 << " " << n - 1;
    else {
        int k = n / min_del;
        std::cout << k << " " << n - k;
    }
}
