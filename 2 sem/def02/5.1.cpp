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
std::vector<int> arr;
int size;
Fenvic(int n) {
    size = n;
    arr.resize(n, 0);
}

void add(int x, long long value) {
    while (x < size) {
        arr[x] += value;
        x = F_1(x);
    }
}
int pref(int x) {
    if (x < 0) {
        return 0;
    }
    long long result = 0;
    while (x >= 0) {
        result += arr[x];
        x = F(x) - 1;
    }
    return result;
}

long long sum(int l, int r) {
    return pref(r) - pref(l - 1);
}
};

int main() {
    int n;
    std::cin >> n;
    Fenvic fenv(n);
    for (int i = 0; i < n; i++) {
        char a;
        std::cin >> a;
        if (a == 'a') fenv.add(i, 0);
        else fenv.add(i, 1);
    }
    int answ = 0;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j+=2) {
            int count = fenv.sum(i, j);
            int len = j - i + 1;
            if (count!=0 && len%count == 0 && len / count == 2) answ+=1;
        }
    }
    std::cout << answ;
}