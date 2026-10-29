#include <iostream>
#include <vector>
#include <unordered_map>

long long count_degree(long long x, long long p) {
    long long cnt = 0;
    while (x % p == 0) {
        x /= p;
        cnt++;
    }
    return cnt;
}

int main() {
    long long a;
    std::cin >> a;
    long long tmp = a;
    std::vector<std::pair<long long, long long>> del;
    long long max_deg = -1;
    for (int i = 2; i*i <= a; i++) {
        if (a % i == 0){
            long long deg = 1;
            a/=i;
            while(a%i == 0) {
                a/=i;
                deg++;
            }
            del.push_back({i, deg});
            if (deg > max_deg) max_deg = deg;
        }
    }
    if (a > 1) {
        del.push_back({a, 1});
    }
    long long answ = 1;
    for (auto a : del) {
        answ *= a.first;
    }

    for (long long i = 1; i <= max_deg; i++) {
        long long x = answ * i;
        bool flag = true;
        for (auto elem : del) {
            long long p = elem.first;
            long long deg = elem.second;
            long long cnt = count_degree(x, p);
            if (cnt * x < deg) {
                flag = false;
                break;
            }
        }
        if (flag){ 
            std::cout << x;
            return 0;
        }
    }
    std::cout << tmp;
}
