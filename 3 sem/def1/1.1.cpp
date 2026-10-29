#include <iostream>
#include <vector>

std::vector<int> prefix_fun(std::vector<int> &s) {
    int n = s.size();
    std::vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        int k = p[i-1];
        while (s[i] != s[k] && k > 0) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            p[i] = k + 1;
        }
    }
    return p;
}

int main() {
    int n;
    std::cin>>n;
    std::vector<int> v;
    for (int i = 0; i< n; i++) {
        int a;
        std::cin >> a;
        v.push_back(a);
    }
    std::vector<int> p = prefix_fun(v);
    for (auto a : p) std::cout << a << " ";
}