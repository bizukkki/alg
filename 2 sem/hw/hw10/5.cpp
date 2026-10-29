#include <iostream>
#include <vector>

int F(int x) {
    return x & (x + 1);
}
int F_1(int x) {
    return x | (x + 1);
}

class Fenvic {
public:
std::vector<std::vector<long long>> arr;
int size;
Fenvic(int n) {
    size = n;
    arr.resize(n, std::vector<long long>(n, 0));
}

void add(int x, int y, long long value) {
    while (x < size) {
        int j = y;
        while (j < size) {
            arr[x][j] += value;
            j = F_1(j);
        }
        x = F_1(x);
    }
}
long long pref(int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    }
    long long result = 0;
    while (x >= 0) {
        int j = y;
        while (j >= 0) {
            result += arr[x][j];
            j = F(j) - 1;
        }
        x = F(x) - 1;
    }
    return result;
}

long long sum(int l, int b, int r, int t) {
    return pref(r, t) - pref(l - 1, t) - pref(r, b - 1) + pref(l - 1, b - 1);
}
};

int main() {
    int n, type;
    std::cin >> type >> n;
    Fenvic fenv(n);
    int x, y, l, b, r, t;
    long long a;
    while (type!=3) {
        std::cin>>type;
        if (type == 1) {
            std::cin >> x >> y >> a;
            fenv.add(x, y, a);
        } else if (type == 2) {
            std::cin >> l >> b >> r >> t;
            std::cout << fenv.sum(l, b, r, t) << "\n";
        }
    }
}