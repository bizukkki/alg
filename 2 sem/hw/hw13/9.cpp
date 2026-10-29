#include <iostream>
#include <vector>
#include <numeric> 

long long gcd(long long a, long long b) {
    while (b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n + 1);
    for (int i = 1; i < n + 1; i++) {
        std::cin >> vec[i];
    }
    std::vector<bool> used(n+1, false);
    std::vector<std::vector<int>> cycles;
    for (int i = 1; i < n + 1; i++) {
        if(used[i]) continue;
        std::vector<int> cycl;
        cycl.push_back(i);
        int now = vec[i];
        used[i] = true;
        while (now != i) {
            cycl.push_back(now);
            used[now] = true;
            now = vec[now];
        }
        cycles.push_back(cycl);
    }
    if (cycles.size() == 1) {
        std::cout << cycles[0].size();
        return 0;
    }
    int nok = cycles[0].size();
    for (size_t i = 1; i < cycles.size(); i++) {
        nok = std::lcm(nok, cycles[i].size());
    }
    std::cout << nok;
}